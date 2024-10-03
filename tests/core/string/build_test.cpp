/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/build.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Build information", "[core][build]")
{
	SECTION("Project name has been generated correctly.")
	{
		STATIC_REQUIRE(!imfy::build_information.name.empty());
	}

	SECTION("Project version has been generated correctly.")
	{
		STATIC_REQUIRE(
				imfy::build_information.version.major > 0U || imfy::build_information.version.minor > 0U ||
				imfy::build_information.version.patch > 0U
		);
	}

	SECTION("Project description has been generated correctly.")
	{
		STATIC_REQUIRE(!imfy::build_information.description.empty());
	}

	SECTION("Project license has been generated correctly.")
	{
		STATIC_REQUIRE(!imfy::build_information.license_name.empty());
	}

	SECTION("imfy::project_version has been generated correctly.")
	{
		STATIC_REQUIRE(
				imfy::build_information.version.major > 0U || imfy::build_information.version.minor > 0U ||
				imfy::build_information.version.patch > 0U
		);
	}

	SECTION("imfy::project_build_type has been generated correctly.")
	{
		STATIC_REQUIRE(!imfy::project_build_type().empty());
	}
}
