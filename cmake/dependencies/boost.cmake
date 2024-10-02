# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

find_package(Boost 1.73 REQUIRED COMPONENTS
	# Support UTF-8 on Windows.
	nowide
	# Use UTF-8 when converting char*/string to filesystem::path and vice-versa.
	filesystem
)

add_dependency_metadata(
	NAME Boost
	VERSION ${Boost_VERSION}
	DESCRIPTION "The Boost project provides free peer-reviewed portable C++ source libraries."
	LICENSE_NAME "Boost Software License 1.0"
)
