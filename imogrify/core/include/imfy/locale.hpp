/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace imfy::locale
{

/** Use UTF-8 as the default encoding for Boost.Filesystem and the global C++ locale. */
void initialize();

} // namespace imfy::locale
