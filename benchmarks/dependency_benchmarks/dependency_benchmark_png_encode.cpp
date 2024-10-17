/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/bench/encode_libpng.hpp>
#include <imfy/bench/encode_lodepng.hpp>
#include <imfy/bench/encode_spng.hpp>
#include <imfy/bench/raw_image_generator.hpp>
#include <imfy/image_format.hpp>

#include <fmt/base.h>
#include <fmt/format.h>
#include <magic_enum.hpp>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <locale>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

namespace
{

consteval imfy::png_color_type get_color_enum_from_channels(const std::uint8_t channels)
{
	// Imogrify and all encoding libraries use the same values for this.
	imfy::png_color_type color_enum{};
	switch (channels)
	{
		case 1U:
			color_enum = imfy::png_color_type::gray;
			break;
		case 2U:
			color_enum = imfy::png_color_type::ga;
			break;
		case 3U:
			color_enum = imfy::png_color_type::rgb;
			break;
		default:
		case 4U:
			color_enum = imfy::png_color_type::rgba;
			break;
	}

	return color_enum;
}

using namespace std::literals::string_view_literals;
constexpr std::array table_headers{
		"library"sv, "file diff"sv, "file size"sv, "relative"sv, "ns/op"sv, "op/s"sv, "err%"sv,
#if ANKERL_NANOBENCH(PERF_COUNTERS)
		"ins/op"sv,	 "cyc/op"sv,		"ins/cyc"sv,	 "bra/op"sv,	 "miss%"sv,
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)
		"total"sv,
};

struct separate_thousands_with_spaces : std::numpunct<char>
{
	char_type do_thousands_sep() const override { return ' '; }
	string_type do_grouping() const override { return "\3"; }
};

std::string table_size_diff(const std::locale& locale, const std::ptrdiff_t value)
{
	constexpr auto format_size = "{:L} B"sv;
	return fmt::format(locale, format_size, value);
}

std::string table_size(const std::locale& locale, const std::size_t value)
{
	return table_size_diff(locale, static_cast<std::ptrdiff_t>(value));
}

std::string table_double(const std::locale& locale, const double value, bool percent = false)
{
	constexpr auto format_double = "{:.1Lf}"sv;
	constexpr auto format_percent = "{:.1Lf}%"sv;
	std::string result{};
	if (percent)
	{
		result = fmt::format(locale, format_percent, value);
	}
	else
	{
		result = fmt::format(locale, format_double, value);
	}

	// Remove trailing decimals if zero.
	if (result.ends_with(".0"sv))
	{
		result = result.substr(0U, result.size() - 2U);
	}

	return result;
}

std::vector<std::vector<std::string>> get_table_from_result(
		const std::array<std::size_t, 3U>& sizes, const ankerl::nanobench::Bench& bench
)
{
	auto thousands = std::make_unique<separate_thousands_with_spaces>();
	const std::locale thousands_separator_locale{std::locale(), thousands.release()};

	using ankerl::nanobench::Result;
	const auto baseline_size = static_cast<double>(sizes[0U]);
	const auto baseline_median = bench.results().front().median(Result::Measure::elapsed);

	std::vector<std::vector<std::string>> table_data;

	for (std::size_t result_index{}; result_index < bench.results().size(); ++result_index)
	{
		const auto& result = bench.results()[result_index];
		const auto current_size = sizes[result_index];
		const auto size_difference = static_cast<std::ptrdiff_t>(current_size) - static_cast<std::ptrdiff_t>(baseline_size);
		const auto median = result.median(Result::Measure::elapsed);
		const auto relative_time = median <= 0.0 ? 0.0 : baseline_median / median * 100.0;
		const auto ns_per_op = median / (bench.timeUnit().count() * bench.batch());
		const auto op_per_s = median <= 0.0 ? 0.0 : bench.batch() / median;
		const auto error_median = result.medianAbsolutePercentError(Result::Measure::elapsed) * 100.0;
#if ANKERL_NANOBENCH(PERF_COUNTERS)
		const bool counters = bench.performanceCounters();
		const auto instructions_per_op = counters && result.has(Result::Measure::instructions)
																				 ? result.median(Result::Measure::instructions) / bench.batch()
																				 : -1.0;
		const auto cycles_per_op = counters && result.has(Result::Measure::cpucycles)
																	 ? result.median(Result::Measure::cpucycles) / bench.batch()
																	 : -1.0;
		const auto instructions_per_cycle = instructions_per_op > 0.0 && cycles_per_op > 0.0
																						? result.median(Result::Measure::cpucycles) / bench.batch()
																						: -1.0;

		const auto branches_median = counters && result.has(Result::Measure::branchinstructions)
																		 ? result.median(Result::Measure::branchinstructions)
																		 : -1.0;
		const auto branches_per_op = branches_median > 0.0 ? branches_median / bench.batch() : -1.0;

		const auto branch_misses = branches_median > 1e-9 && result.has(Result::Measure::branchmisses)
																	 ? 100.0 * result.median(Result::Measure::branchmisses) / branches_median
																	 : -1.0;
		const auto total = result.sumProduct(Result::Measure::iterations, Result::Measure::elapsed);
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)

		table_data.emplace_back(std::vector<std::string>{
				result.config().mBenchmarkName, table_size_diff(thousands_separator_locale, size_difference),
				table_size(thousands_separator_locale, current_size),
				table_double(thousands_separator_locale, relative_time, true),
				table_double(thousands_separator_locale, ns_per_op), table_double(thousands_separator_locale, op_per_s),
				table_double(thousands_separator_locale, error_median),
#if ANKERL_NANOBENCH(PERF_COUNTERS)
				table_double(thousands_separator_locale, instructions_per_op),
				table_double(thousands_separator_locale, cycles_per_op),
				table_double(thousands_separator_locale, instructions_per_cycle),
				table_double(thousands_separator_locale, branches_per_op),
				table_double(thousands_separator_locale, branch_misses),
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)
				table_double(thousands_separator_locale, total)
		});
	}

	return table_data;
}

std::array<std::size_t, table_headers.size()> calculate_cell_width(
		const std::vector<std::vector<std::string>>& table_data
)
{
	constexpr std::size_t cell_padding = 2U;
	std::array<std::size_t, table_headers.size()> cell_width{};
	for (std::size_t cell_index{}; cell_index < cell_width.size(); ++cell_index)
	{
		cell_width[cell_index] = table_headers[cell_index].size() + cell_padding;
	}

	for (std::size_t cell_index{}; cell_index < cell_width.size(); ++cell_index)
	{
		for (const auto& row : table_data)
		{
			cell_width[cell_index] = std::max(cell_width[cell_index], row[cell_index].size() + cell_padding);
		}
	}

	return cell_width;
}

void print_table(const std::vector<std::vector<std::string>>& table_data)
{
	const auto cell_width = calculate_cell_width(table_data);

	// Note that both formats add an extra character at the end for right padding.
	constexpr auto cell_format = "|{0: >{1}} "sv;
	constexpr auto header_separator_format = "|{0:->{1}}-"sv;
	constexpr auto row_end = "|"sv;

	for (std::size_t cell_index{}; cell_index < cell_width.size(); ++cell_index)
	{
		fmt::print(cell_format, table_headers[cell_index], cell_width[cell_index]);
	}
	fmt::println(row_end);
	for (const std::size_t current_width : cell_width)
	{
		fmt::print(header_separator_format, ""sv, current_width);
	}
	fmt::println(row_end);

	for (const auto& row : table_data)
	{
		for (std::size_t cell_index{}; cell_index < cell_width.size(); ++cell_index)
		{
			fmt::print(cell_format, row[cell_index], cell_width[cell_index]);
		}
		fmt::println(row_end);
	}
	fmt::print("\n"sv);
}

template <typename RawImage>
void benchmark_compare_libraries(
		ankerl::nanobench::Bench& bench, std::uint32_t width, std::uint32_t height, std::uint8_t compression_level
)
{
	constexpr auto color_enum = get_color_enum_from_channels(RawImage::channels);
	constexpr std::uint8_t bit_depth = RawImage::bit_depth;
	constexpr auto color_type = static_cast<std::uint8_t>(color_enum);

	const RawImage image{width, height};
	bench.title(fmt::format(
			"Size: {:d}x{:d}, color type: {:s}, bit depth: {:d}"sv, width, height, magic_enum::enum_name(color_enum),
			bit_depth
	));

	// libpng is executed first to serve as the baseline for PNG benchmarking.
	std::array<std::size_t, 3U> sizes{};
	bench.run(
			"libpng",
			[&]()
			{
				sizes[0U] = imfy::bench::encode_libpng(width, height, image.buffer(), color_type, bit_depth, compression_level);
			}
	);
	bench.run(
			"lodepng",
			[&]() { sizes[1U] = imfy::bench::encode_lodepng(width, height, image.buffer(), color_type, bit_depth); }
	);
	bench.run(
			"spng", [&]()
			{ sizes[2U] = imfy::bench::encode_spng(width, height, image.buffer(), color_type, bit_depth, compression_level); }
	);

	fmt::println("### {:s}\n", bench.title());
	print_table(get_table_from_result(sizes, bench));
}

} // Anonymous namespace

int main()
{
	ankerl::nanobench::Bench bench;
	// libpng will be used as the baseline.
	bench.relative(true);
	// Enable performance counters feature. Only available on Linux.
#if ANKERL_NANOBENCH(PERF_COUNTERS)
	bench.performanceCounters(true);
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)
	// Disable nanobench rendering.
	bench.output(nullptr);

	fmt::println("# Image encoding benchmarks\n");
	// Default level for both libpng and spng.
	constexpr auto zlib_compression_level = 6;
	fmt::println("## Library comparisons\n");
	benchmark_compare_libraries<imfy::bench::raw_image<4U, 1U>>(bench, 128U, 128U, zlib_compression_level);	 // NOLINT
	benchmark_compare_libraries<imfy::bench::raw_image<4U, 1U>>(bench, 1024U, 128U, zlib_compression_level); // NOLINT
	benchmark_compare_libraries<imfy::bench::raw_image<4U, 1U>>(bench, 128U, 1024U, zlib_compression_level); // NOLINT
	benchmark_compare_libraries<imfy::bench::raw_image<2U, 2U>>(bench, 128U, 128U, zlib_compression_level);	 // NOLINT
}
