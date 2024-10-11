# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_library(imogrify_arguments STATIC
	include/imfy/image_format.hpp
	image_format.cpp
)

target_include_directories(imogrify_arguments PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>/include
)

target_compile_options(imogrify_arguments PRIVATE ${IMOGRIFY_CPP_WARNING_FLAGS})

target_link_libraries(imogrify_arguments PRIVATE
	magic_enum::magic_enum
	imogrify_core
)
