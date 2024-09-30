# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_library(imogrify_locale STATIC
	include/imfy/locale.hpp
	locale.cpp
)

target_include_directories(imogrify_locale PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include
)

target_compile_options(imogrify_locale PRIVATE ${IMOGRIFY_CPP_WARNING_FLAGS})

target_link_libraries(imogrify_locale PRIVATE
	Boost::filesystem
	Boost::nowide
)
