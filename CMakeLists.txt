# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.25)

include(cmake/options.cmake)
include(cmake/dependency_data.cmake)
include(cmake/dependencies/vcpkg.cmake)

if (POLICY CMP0167)
	# FindBoost module is removed policy.
	cmake_policy(SET CMP0167 NEW)
endif ()

project(imogrify
	VERSION 0.1.0
	DESCRIPTION "Image conversion tool optimized for processing large batches of files."
	HOMEPAGE_URL "https://github.com/joseasoler/imogrify"
	LANGUAGES C CXX
)

# The project uses C++20 without any non-standard compiler extensions.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/compiler_support.cmake)
include(cmake/operative_system_support.cmake)

include(cmake/clang_tidy.cmake)
include(cmake/compiler_warnings.cmake)

include(cmake/dependencies/boost.cmake)
include(cmake/dependencies/catch2.cmake)
include(cmake/dependencies/fmt.cmake)
include(cmake/dependencies/libpng.cmake)
include(cmake/dependencies/magic_enum.cmake)

add_subdirectory(imogrify)

if (IMOGRIFY_BUILD_UNIT_TESTS)
	add_subdirectory(tests)
	enable_testing()
	add_test(NAME imogrify_unit_tests COMMAND $<TARGET_FILE:imogrify_unit_tests>)
endif ()