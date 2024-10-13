/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/path.hpp>

#include <cstdint>
#include <string_view>

namespace imfy
{

/** @brief Image formats supported by imogrify.
 * See *_image_format_type enums for specific types for each image
 */
enum class image_format : std::uint8_t
{
	/** Only valid for certain options such as alpha image output. */
	none = 0U,
	/** Portable Network Graphics. */
	png,
};

/** Parse an image format value from user input. */
[[nodiscard]] image_format image_format_from_input(std::string_view input);

/** Checks if a file has an extension belonging to the chosen image format. */
[[nodiscard]] bool file_matches_image_format(image_format type, fs::path_view file_path);

/** See http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html#C.IHDR for details. */
enum class png_color_type : std::uint8_t
{
	gray = 0U,
	rgb = 2U,
	palette = 3U,
	ga = 4U,
	rgba = 6U,
};

/** Imogrify does not offer support for bit depths smaller than 8. 16 is not supported for palette color types.
 * See http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html#C.IHDR for details.
 */
enum class png_bit_depth : std::uint8_t
{
	eight = 8U,
	sixteen = 16U,
};

struct png_information final
{
	png_color_type color_type;
	png_bit_depth bit_depth;
};

} // namespace imfy
