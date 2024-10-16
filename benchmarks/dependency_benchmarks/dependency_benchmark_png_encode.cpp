/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/bench/encode_libpng.hpp>
#include <imfy/bench/encode_spng.hpp>
#include <imfy/bench/raw_image_generator.hpp>
#include <imfy/image_format.hpp>

#include <cstdint>
#include <cstring>
#include <iostream>

#define ANKERL_NANOBENCH_IMPLEMENT

#include "imfy/bench/encode_lodepng.hpp"

#include <nanobench.h>

namespace
{

} // Anonymous namespace

int main()
{
	ankerl::nanobench::Bench bench;
	// libpng will be used as the baseline.
	bench.relative(true);
	// Enable performance counters feature.
	bench.performanceCounters(true);

	// Default level for both libpng and spng.
	constexpr auto zlib_compression_level = 6;

	const auto size = 256U;
	constexpr std::uint8_t channels = 4U;
	constexpr std::uint8_t byte_depth = 1U;
	constexpr std::uint8_t bit_depth = byte_depth * 8U;
	imfy::bench::raw_image<channels, byte_depth> image{size, size};

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

	const auto color_type = static_cast<std::uint8_t>(color_enum);
	// libpng is the baseline for PNG benchmarking.
	std::size_t libpng_size{};
	bench.run(
			"libpng",
			[&]()
			{
				libpng_size =
						imfy::bench::encode_libpng(size, size, image.buffer(), color_type, bit_depth, zlib_compression_level);
			}
	);
	std::size_t lodepng_size{};
	bench.run(
			"lodepng",
			[&]() { lodepng_size = imfy::bench::encode_lodepng(size, size, image.buffer(), color_type, bit_depth); }
	);
	std::size_t spng_size{};
	bench.run(
			"spng",
			[&]()
			{
				spng_size = imfy::bench::encode_spng(size, size, image.buffer(), color_type, bit_depth, zlib_compression_level);
			}
	);

	std::cout << '\n';
	std::cout << "libpng: " << libpng_size << "B\n";
	std::cout << "lodepng: " << lodepng_size << "B\n";
	std::cout << "spng: " << spng_size << "B\n";
}
