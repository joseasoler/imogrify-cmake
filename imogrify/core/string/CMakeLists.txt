# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_library(imogrify_string INTERFACE
	include/imfy/string_view.hpp
)

target_include_directories(imogrify_string INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include
)
