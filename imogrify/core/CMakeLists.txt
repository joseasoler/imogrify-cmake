# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_library(imogrify_core STATIC
	include/imfy/allocator.hpp
	include/imfy/locale.hpp
	include/imfy/string_view.hpp
	locale.cpp
)

target_include_directories(imogrify_core PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include
)

target_compile_options(imogrify_core PRIVATE ${IMOGRIFY_CPP_WARNING_FLAGS})

target_link_libraries(imogrify_core PRIVATE
	Boost::filesystem
	Boost::nowide
)
