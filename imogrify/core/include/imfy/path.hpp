/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <boost/filesystem/path.hpp>

#include <string_view>

namespace imfy::fs
{

/** Convenience alias for a filesystem path. */
using path = boost::filesystem::path;

/** Non-owning view to a filesystem path.
 * The underlying character type depends on the native encoding of the filesystem in the OS.
 */
using path_view = std::basic_string_view<path::value_type>;

#if IMOGRIFY_OS_WINDOWS
/** Cross-platform helper for defining string literals of the type expected by path_view. */
#define PATH_LITERAL(literal) L##literal
#else
/** Cross-platform helper for defining string literals of the type expected by path_view. */
#define PATH_LITERAL(literal) literal
#endif // IMOGRIFY_OS_WINDOWS

/**
 * Case insensitive check for files having the specified extension.
 * @param extension Must be in lower case and it should not include the . character.
 * @param file_path Path to check.
 * @return True if the file referenced by the path has the extension.
 */
bool has_extension(path_view extension, const path& file_path);

} // namespace imfy::fs
