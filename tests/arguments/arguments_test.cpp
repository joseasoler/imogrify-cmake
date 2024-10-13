/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/arguments.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Argument type tests", "[arguments][arguments]")
{
	STATIC_REQUIRE(sizeof(imfy::output_information) <= 4U);
}