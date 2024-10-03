/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/string_view.hpp>
#include <imfy/version.hpp>

namespace imfy
{

/** Stores compile-time information about dependencies.
 */
struct dependency_t
{
	/** Name of the library. */
	string_view name;

	/** <A HREF="https://semver.org/">Semantic version_t</A> being used. */
	version_t version;

	/** Short description of the library */
	string_view description;

	/** Short name of the library's license. */
	string_view license_name;
};

} // namespace imfy