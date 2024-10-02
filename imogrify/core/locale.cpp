/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "include/imfy/locale.hpp"

#include <boost/nowide/filesystem.hpp>

#include <locale>

namespace imfy::locale
{

void initialize()
{
	std::locale::global(boost::nowide::nowide_filesystem());
}

} // namespace imfy::locale
