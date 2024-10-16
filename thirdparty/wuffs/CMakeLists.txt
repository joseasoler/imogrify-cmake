# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_library(wuffs INTERFACE)

target_sources(wuffs INTERFACE
	wuffs.c
)

target_include_directories(wuffs SYSTEM INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
