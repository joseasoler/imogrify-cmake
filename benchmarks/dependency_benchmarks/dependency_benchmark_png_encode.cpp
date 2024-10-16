/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#define ANKERL_NANOBENCH_IMPLEMENT

#include <nanobench.h>
#include <png.h>

#include <array>
#include <type_traits>
#include <vector>

namespace
{
constexpr std::size_t image_size{128U};
constexpr std::size_t channels{4U};
using raw_image = std::array<std::uint8_t, image_size * image_size * channels>;

consteval raw_image get_raw_image()
{
	raw_image image{};
	constexpr std::array<std::uint8_t, channels> channel_modulo{255, 254, 253, 252};
	for (std::size_t pixel_index = 0U; pixel_index < image.size(); pixel_index += channels)
	{
		image[pixel_index] = pixel_index % channel_modulo[0];
		image[pixel_index + 1] = pixel_index % channel_modulo[1];
		image[pixel_index + 2] = pixel_index % channel_modulo[2];
		image[pixel_index + 3] = pixel_index % channel_modulo[3];
	}

	return image;
}

constexpr raw_image image = get_raw_image();

// ToDo port everything libpng related to its own module.

static_assert(std::is_same_v<png_voidp, void*>);
static_assert(std::is_same_v<png_bytep, std::uint8_t*>);
static_assert(std::is_same_v<png_bytepp, std::uint8_t**>);
static_assert(std::is_same_v<png_size_t, std::size_t>);

void write_data_to_buffer(png_struct* png_ptr, std::uint8_t* data, std::size_t write_length)
{
	auto& output_buffer = *static_cast<std::vector<std::uint8_t>*>(png_get_io_ptr(png_ptr));
	const auto current_size = output_buffer.size();
	const auto new_size = current_size + write_length;
	if (output_buffer.size() < new_size)
	{
		output_buffer.resize(new_size);
	}

	std::memcpy(&output_buffer[current_size], data, write_length);
}

} // Anonymous namespace

void encode_with_libpng()
{
	auto* png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (png_ptr == nullptr)
	{
		return;
	}

	auto* info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == nullptr)
	{
		png_destroy_write_struct(&png_ptr, nullptr);
		return;
	}

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return;
	}

	png_set_IHDR(
			png_ptr, info_ptr, image_size, image_size, std::numeric_limits<std::uint8_t>::digits, PNG_COLOR_TYPE_RGBA,
			PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT
	);

	png_init_io(png_ptr, fp);

	std::array<std::uint8_t*, image_size> row_pointers{};
	for (std::size_t row_index = 0U; row_index < image_size; ++row_index)
	{
		row_pointers[row_index] = const_cast<std::uint8_t*>(&image[row_index * image_size * channels]);
	}

	png_set_rows(png_ptr, info_ptr, row_pointers.data());

	std::vector<std::uint8_t> buffer{};
	png_set_write_fn(png_ptr, &buffer, write_data_to_buffer, nullptr);
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, nullptr);

	png_destroy_write_struct(&png_ptr, &info_ptr);

	// ToDo temporarily dump buffer into a file.
}

int main()
{
	ankerl::nanobench::Bench bench;
	bench.title("PNG encoding");
	// Encode the image twice before measuring.
	bench.warmup(2U);
	// libpng will be used as the baseline.
	bench.relative(true);
	// Enable performance counters feature.
	bench.performanceCounters(true);

	// libpng will be the baseline for the benchmark.
	bench.run("libpng", encode_with_libpng);

	// ToDo libpng Runtime optimization
}
}