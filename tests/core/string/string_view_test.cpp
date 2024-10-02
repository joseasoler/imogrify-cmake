/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <catch2/catch_test_macros.hpp>

#include "imfy/string_view.hpp"

TEST_CASE("imfy::string_view coherence checks", "[core][string_view]")
{
	constexpr imfy::string_view test_view{"ÑÇΣѮф"};
	STATIC_REQUIRE(test_view.size() >= 5U);
}