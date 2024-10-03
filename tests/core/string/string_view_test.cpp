/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/string_view.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("imfy::string_view coherence checks", "[core][string_view]")
{
	using namespace imfy::literals::string_view_literals;
	constexpr auto test_view{"ÑÇΣѮф"_sv};
	STATIC_REQUIRE(test_view.size() >= 5U);
}