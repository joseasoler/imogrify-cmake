/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/image_format.hpp"

#include <imfy/path.hpp>

#include <png.h>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Get image format from input", "[arguments][image_format]")
{
	REQUIRE(imfy::image_format_from_input("") == imfy::image_format::none);
	REQUIRE(imfy::image_format_from_input("png") == imfy::image_format::png);
	REQUIRE(imfy::image_format_from_input("Png") == imfy::image_format::png);
	REQUIRE(imfy::image_format_from_input("PnG") == imfy::image_format::png);
	REQUIRE(imfy::image_format_from_input("pNG") == imfy::image_format::png);
	REQUIRE(imfy::image_format_from_input("apng") == imfy::image_format::none);
}

TEST_CASE("None Image format extension tests", "[arguments][image_format]")
{
	REQUIRE(!imfy::file_matches_image_format(imfy::image_format::none, PATH_LITERAL("file.none")));
	REQUIRE(!imfy::file_matches_image_format(imfy::image_format::none, PATH_LITERAL("file.png")));
	REQUIRE(!imfy::file_matches_image_format(imfy::image_format::none, PATH_LITERAL("file.jpg")));
	REQUIRE(!imfy::file_matches_image_format(imfy::image_format::none, PATH_LITERAL("file")));
}

TEST_CASE("PNG Image format extension tests", "[arguments][image_format]")
{
	REQUIRE(imfy::file_matches_image_format(imfy::image_format::png, PATH_LITERAL("file.png")));
	REQUIRE(!imfy::file_matches_image_format(imfy::image_format::png, PATH_LITERAL("file.apng")));
	REQUIRE(!imfy::file_matches_image_format(imfy::image_format::png, PATH_LITERAL("file")));
}

TEST_CASE("PNG format information tests", "[arguments][image_format]")
{
	STATIC_REQUIRE(static_cast<int>(imfy::png_color_type::gray) == PNG_COLOR_TYPE_GRAY);
	STATIC_REQUIRE(static_cast<int>(imfy::png_color_type::rgb) == PNG_COLOR_TYPE_RGB);
	STATIC_REQUIRE(static_cast<int>(imfy::png_color_type::palette) == PNG_COLOR_TYPE_PALETTE);
	STATIC_REQUIRE(static_cast<int>(imfy::png_color_type::ga) == PNG_COLOR_TYPE_GRAY_ALPHA);
	STATIC_REQUIRE(static_cast<int>(imfy::png_color_type::rgba) == PNG_COLOR_TYPE_RGB_ALPHA);
	STATIC_REQUIRE(sizeof(imfy::png_information) == 2U);
}