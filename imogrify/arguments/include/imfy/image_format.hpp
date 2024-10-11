/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/path.hpp>

#include <cstdint>

namespace imfy
{

/** Underlying primitive type used by every *_image_format_type enum and the image_file_type enum. */
using image_format_t = std::uint8_t;

/** @brief Image formats supported by imogrify.
 * See *_image_format_type enums for specific types for each image
 */
enum class image_format : image_format_t
{
	/** Only valid for certain options such as alpha image output. */
	none = 0U,
	/** Portable Network Graphics. */
	png,
};

[[nodiscard]] bool file_matches_image_format(image_format type, fs::path_view file_path);

enum class png_image_format : image_format_t
{
	/** Palette with 8 bits per channel. */
	palette_8,
	/** Grayscale with 8 bits per channel. */
	gray_8,
	/** Grayscale with 16 bits per channel. */
	gray_16,
	/** Grayscale and alpha with 8 bits per channel. */
	ga_8,
	/** Grayscale and alpha with 16 bits per channel. */
	ga_16,
	/** RGB with 8 bits per channel. */
	rgb_8,
	/** RGB with 16 bits per channel. */
	rgb_16,
	/** RGBA with 8 bits per channel. */
	rgba_8,
	/** RGBA with 16 bits per channel. */
	rgba_16,
};

} // namespace imfy
