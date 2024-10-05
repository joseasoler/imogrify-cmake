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

# The main Boost project is mentioned as we are using core parts of it through the other dependencies.
add_dependency_metadata(
	NAME Boost
	VERSION ${Boost_VERSION}
	DESCRIPTION "The Boost project provides free peer-reviewed portable C++ source libraries."
	LICENSE_NAME "Boost Software License 1.0"
)

# Then each separate library is listed explicitly.
add_dependency_metadata(
	NAME Boost.NoWide
	VERSION ${Boost_VERSION}
	DESCRIPTION "A library that makes cross platform Unicode aware programming easier."
	LICENSE_NAME "Boost Software License 1.0"
)

add_dependency_metadata(
	NAME Boost.Filesystem
	VERSION ${Boost_VERSION}
	DESCRIPTION "Provides portable facilities to query and manipulate paths, files, and directories."
	LICENSE_NAME "Boost Software License 1.0"
)

add_dependency_metadata(
	NAME Boost.Predef
	VERSION ${Boost_VERSION}
	DESCRIPTION "Defines a set of compiler, architecture, operating system, library, and other version numbers."
	LICENSE_NAME "Boost Software License 1.0"
)

