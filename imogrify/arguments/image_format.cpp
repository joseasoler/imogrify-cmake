/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "include/imfy/image_format.hpp"

#include <imfy/path.hpp>

#include <array>

namespace
{
// The forward slash character is forbidden in both Unix and Windows systems.
constexpr std::array image_format_extensions{PATH_LITERAL("/"), PATH_LITERAL("png")};

} // Anonymous namespace

namespace imfy
{

bool file_matches_image_format(image_format type, fs::path_view file_path)
{
	return fs::has_extension(image_format_extensions[static_cast<std::size_t>(type)], file_path);
}

} // namespace imfy
