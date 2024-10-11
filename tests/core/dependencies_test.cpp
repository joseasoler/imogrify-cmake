/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/dependencies.hpp"

#include <algorithm>
#include <string_view>

#include "imfy/dependency.hpp"
#include "imfy/version.hpp"

#include <catch2/catch_test_macros.hpp>
namespace
{

constexpr char to_lower(const char character)
{
	return character >= 'A' && character <= 'Z' ? static_cast<char>(character + 'a' - 'A') : character;
}

struct is_case_insensitive_less final
{
	constexpr bool operator()(const imfy::dependency_t& lhs, const imfy::dependency_t& rhs)
	{
		return std::lexicographical_compare(
				lhs.name.cbegin(), lhs.name.cend(), rhs.name.cbegin(), rhs.name.cend(),
				[](const char left, const char right) { return to_lower(left) < to_lower(right); }
		);
	}
};

template <typename array>
[[nodiscard]] constexpr bool is_in_sorted_array(const array& arr, const std::string_view& str_view)
{
	const auto iterator = std::lower_bound(std::cbegin(arr), std::cend(arr), str_view);
	return iterator != std::cend(arr) && (*iterator) == str_view;
}

} // Anonymous namespace

TEST_CASE("imfy::dependencies array", "[core][dependencies]")
{
	using imfy::dependencies;
	using imfy::dependency_t;

	SECTION("Dependencies have been generated.")
	{
		STATIC_REQUIRE(std::size(dependencies) > 0U);
	}

	SECTION("The dependencies array is sorted by name.")
	{
		STATIC_REQUIRE(std::is_sorted(std::cbegin(dependencies), std::cend(dependencies), is_case_insensitive_less{}));
	}
}

TEST_CASE("imfy::dependencies values", "[core][dependencies]")
{
	using imfy::dependencies;
	using imfy::dependency_t;
	using imfy::version_t;

	SECTION("All dependencies have a name.")
	{
		STATIC_REQUIRE(std::all_of(
				std::cbegin(dependencies), std::cend(dependencies),
				[](const dependency_t& dependency) -> bool { return !dependency.name.empty(); }
		));
	}

	SECTION("All dependencies have a valid version.")
	{
		STATIC_REQUIRE(std::all_of(
				std::cbegin(dependencies), std::cend(dependencies), [](const dependency_t& dependency) -> bool
				{ return dependency.version.major != 0U || dependency.version.minor != 0U || dependency.version.patch != 0U; }
		));
	}

	SECTION("All dependencies have a description.")
	{
		STATIC_REQUIRE(std::all_of(
				std::cbegin(dependencies), std::cend(dependencies),
				[](const dependency_t& dependency) -> bool { return !dependency.description.empty(); }
		));
	}

	SECTION("All dependencies have a license name.")
	{
		STATIC_REQUIRE(std::all_of(
				std::cbegin(dependencies), std::cend(dependencies),
				[](const dependency_t& dependency) -> bool { return !dependency.license_name.empty(); }
		));
	}

	SECTION("All licenses are compatible with Imogrify.")
	{
		using namespace std::literals::string_view_literals;
		constexpr std::array compatible_licenses{"Boost Software License 1.0"sv, "MIT License"sv};
		STATIC_REQUIRE(std::is_sorted(std::cbegin(compatible_licenses), std::cend(compatible_licenses)));

		STATIC_REQUIRE(std::all_of(
				std::cbegin(dependencies), std::cend(dependencies),
				[&compatible_licenses](const dependency_t& dependency) -> bool
				{ return is_in_sorted_array(compatible_licenses, dependency.license_name); }
		));
	}
}