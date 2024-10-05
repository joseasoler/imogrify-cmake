/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/path.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Path utility functions tests", "[core][path]")
{
	using imfy::fs::has_extension;
	using imfy::fs::path;
	using imfy::fs::path_view;

	constexpr path_view png_extension{PATH_LITERAL("png")};

	REQUIRE(!has_extension(png_extension, PATH_LITERAL("file")));
	REQUIRE(!has_extension(png_extension, PATH_LITERAL("file.jpg")));
	REQUIRE(!has_extension(png_extension, PATH_LITERAL("file.apng")));
	REQUIRE(!has_extension(png_extension, PATH_LITERAL("file.pnga")));
	REQUIRE(!has_extension(png_extension, PATH_LITERAL("file.PNGa")));
	REQUIRE(!has_extension(png_extension, PATH_LITERAL("file.png.jpg")));
	REQUIRE(has_extension(png_extension, PATH_LITERAL("file.png")));
	REQUIRE(has_extension(png_extension, PATH_LITERAL("file.pNg")));
	REQUIRE(has_extension(png_extension, PATH_LITERAL("file.PnG")));
	REQUIRE(has_extension(png_extension, PATH_LITERAL("file.PNG")));
}