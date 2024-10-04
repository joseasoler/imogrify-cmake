# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

list(SORT IMOGRIFY_DEPENDENCY_DATA_LIST CASE INSENSITIVE)

string(REPLACE ";" "" IMOGRIFY_DEPENDENCY_DATA_STRING "${IMOGRIFY_DEPENDENCY_DATA_LIST}")

string(REPLACE "GNU" "GCC" IMOGRIFY_COMPILER_NAME "${CMAKE_CXX_COMPILER_ID}")
string(REPLACE "MSVC" "Microsoft Visual C++" IMOGRIFY_COMPILER_NAME "${IMOGRIFY_COMPILER_NAME}")

configure_file(include/imfy/build.hpp.in include/imfy/build.hpp @ONLY)
configure_file(include/imfy/dependencies.hpp.in include/imfy/dependencies.hpp @ONLY)

add_library(imogrify_core STATIC
	${CMAKE_CURRENT_BINARY_DIR}/include/imfy/build.hpp
	${CMAKE_CURRENT_BINARY_DIR}/include/imfy/dependencies.hpp
	include/imfy/locale.hpp
	include/imfy/version.hpp
	locale.cpp
)

target_include_directories(imogrify_core PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>/include
)

target_compile_options(imogrify_core PRIVATE ${IMOGRIFY_CPP_WARNING_FLAGS})

target_link_libraries(imogrify_core PRIVATE
	Boost::filesystem
	Boost::nowide
)
