/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string_view>

namespace imfy
{

/** @brief Non-owning reference to a UTF-8 string.
 *
 * Keep in mind that methods such as length() or size() return the number of bytes required to store the string in
 * memory, which is unrelated to the number of characters in the string. See http://utf8everywhere.org/
 */
using string_view = std::string_view;

} // namespace imfy
