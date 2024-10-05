/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "include/imfy/path.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/predef/os.h>

#include <algorithm>

#if BOOST_OS_WINDOWS
#include <cwctype>
#else
#include <cctype>
#endif // BOOST_OS_WINDOWS

using path_string = imfy::fs::path::string_type;
using path_char = path_string::value_type;

namespace
{

#if BOOST_OS_WINDOWS
constexpr path_char path_separator = L'.';
#else
constexpr path_char path_separator = '.';
#endif // BOOST_OS_WINDOWS

/**
 * Checks if two path views are case insensitive equal.
 * @param lhs This view may have upper case character.
 * @param rhs This view is assumed to be lower-case.
 * @return True if both views have the same set of characters.
 */
bool insensitive_equals(const imfy::fs::path_view lhs, const imfy::fs::path_view rhs)
{
	const auto char_insensitive_equals = [](const path_char lhsc, const path_char rhsc) -> bool
	{
#if BOOST_OS_WINDOWS
		return std::towlower(lhsc) == rhsc;
#else
		return std::tolower(lhsc) == rhsc;
#endif // BOOST_OS_WINDOWS
	};
	return lhs.size() == rhs.size() && std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), char_insensitive_equals);
}

/** Get a view to the path extension without allocating additional path objects. */
imfy::fs::path_view extension_view(const imfy::fs::path& path)
{
	const auto& path_str = path.native();
	const auto pos = path_str.find_last_of(path_separator);
	if (pos == path_string::npos)
	{
		return {};
	}

	return {path_str.cbegin() + static_cast<path_string::difference_type>(pos + 1U), path_str.cend()};
}

} // Anonymous namespace

namespace imfy::fs
{

bool has_extension(path_view extension, const path& file_path)
{
	return insensitive_equals(extension_view(file_path), extension);
}

} // namespace imfy::fs
