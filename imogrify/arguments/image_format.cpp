/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "include/imfy/image_format.hpp"

#include <imfy/path.hpp>

#include <magic_enum.hpp>

#include <array>
#include <cstddef>
#include <string_view>

namespace
{
// The forward slash character is forbidden in both Unix and Windows systems.
constexpr std::array image_format_extensions{PATH_LITERAL("/"), PATH_LITERAL("png")};

} // Anonymous namespace

namespace imfy
{

[[nodiscard]] image_format image_format_from_input(const std::string_view input)
{
	auto parsed_format = magic_enum::enum_cast<image_format>(input, magic_enum::case_insensitive);
	return parsed_format.has_value() ? parsed_format.value() : image_format::none;
}

bool file_matches_image_format(const image_format type, const fs::path_view file_path)
{
	return fs::has_extension(image_format_extensions[static_cast<std::size_t>(type)], file_path);
}

} // namespace imfy
