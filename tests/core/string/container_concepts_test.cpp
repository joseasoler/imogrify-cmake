/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/container_concepts.hpp"

#include <imfy/allocator.hpp>
#include <imfy/dependencies.hpp>
#include <imfy/string_view.hpp>
#include <imfy/vector.hpp>
#include <imfy/version.hpp>

#include <cstdint>
#include <memory>
#include <vector>

#include <catch2/catch_test_macros.hpp>

struct unmovable_t final
{
	unmovable_t() = default;
	unmovable_t(const unmovable_t&) = default;
	unmovable_t(unmovable_t&&) noexcept = delete;
	unmovable_t& operator=(const unmovable_t&) = default;
	unmovable_t& operator=(unmovable_t&&) noexcept = default;
	~unmovable_t() = default;
};

namespace std
{
void swap(unmovable_t& /*lhs*/, unmovable_t& /*rhs*/) noexcept // NOLINT
{
}
} // namespace std

struct movable_exceptions_t final
{
	movable_exceptions_t() = default;
	movable_exceptions_t(const movable_exceptions_t&) = default;
	movable_exceptions_t(movable_exceptions_t&&) { throw std::exception{}; }; // NOLINT
	movable_exceptions_t& operator=(const movable_exceptions_t&) = default;
	movable_exceptions_t& operator=(movable_exceptions_t&&) = default;
	~movable_exceptions_t() = default;
};

namespace std
{
void swap(movable_exceptions_t& /*lhs*/, movable_exceptions_t& /*rhs*/) noexcept // NOLINT
{
}
} // namespace std

TEST_CASE("imfy::is_containable", "[container_concepts][type_traits]")
{
	// Imogrify types.
	SECTION("Imogrify types")
	{
		STATIC_REQUIRE(imfy::is_containable_v<imfy::allocator<std::int8_t>>);
		STATIC_REQUIRE(imfy::is_containable_v<imfy::dependency_t>);
		STATIC_REQUIRE(imfy::is_containable_v<imfy::string_view>);
		STATIC_REQUIRE(imfy::is_containable_v<imfy::version_t>);
	}

	// Other types.
	SECTION("Other types")
	{
		STATIC_REQUIRE(imfy::is_containable_v<std::int32_t>);
		STATIC_REQUIRE(imfy::is_containable_v<std::vector<std::uint64_t*>>);
		STATIC_REQUIRE(imfy::is_containable_v<std::unique_ptr<float>>);
		STATIC_REQUIRE(imfy::is_containable_v<imfy::vector<std::vector<const char*>>>);
	}

	SECTION("Non-containable types")
	{
		STATIC_REQUIRE(!imfy::is_containable_v<unmovable_t>);
		STATIC_REQUIRE(!imfy::is_containable_v<movable_exceptions_t>);
	}
}
