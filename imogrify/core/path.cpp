/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "include/imfy/path.hpp"

#include <boost/filesystem/path.hpp>

#if IMOGRIFY_OS_WINDOWS
#include <cwctype>
#else
#include <cctype>
#endif // IMOGRIFY_OS_WINDOWS

using path_string = boost::filesystem::path::string_type;
using imfy::fs::path_char_t;

namespace
{

#if IMOGRIFY_OS_WINDOWS
constexpr path_char_t path_separator = L'.';
#else
constexpr path_char_t path_separator = '.';
#endif // IMOGRIFY_OS_WINDOWS

/**
 * Checks if two path views are case insensitive equal.
 * @param lhs This view may have upper case character.
 * @param rhs This view is assumed to be lower-case.
 * @return True if both views have the same set of characters.
 */
bool insensitive_equals(const imfy::fs::path_view lhs, const imfy::fs::path_view rhs)
{
	const auto char_insensitive_equals = [](const path_char_t lhsc, const path_char_t rhsc) -> bool
	{
#if IMOGRIFY_OS_WINDOWS
		return std::towlower(lhsc) == rhsc;
#else
		return std::tolower(lhsc) == rhsc;
#endif // IMOGRIFY_OS_WINDOWSs
	};
	return lhs.size() == rhs.size() && std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), char_insensitive_equals);
}

/** Get a view to the path extension without allocating additional path objects. */
imfy::fs::path_view extension_view(imfy::fs::path_view path)
{
	const auto pos = path.find_last_of(path_separator);
	if (pos == path_string::npos)
	{
		return {};
	}

	return {path.cbegin() + static_cast<path_string::difference_type>(pos + 1U), path.cend()};
}

} // Anonymous namespace

namespace imfy::fs
{

bool has_extension(path_view extension, path_view file_path)
{
	return insensitive_equals(extension_view(file_path), extension);
}

} // namespace imfy::fs
