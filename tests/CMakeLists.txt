# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

find_package(Catch2 REQUIRED)

add_executable(imogrify_unit_tests
	tests_main.cpp
	core/build_test.cpp
	core/dependencies_test.cpp
	core/path_test.cpp
	arguments/image_format_test.cpp
)

target_link_libraries(imogrify_unit_tests PRIVATE
	Catch2::Catch2
	imogrify_core
	imogrify_arguments
)

