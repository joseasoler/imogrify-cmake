# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

find_package(Catch2 REQUIRED)

add_executable(imogrify_tests
	tests_main.cpp
	core/string/container_concepts_test.cpp
	core/string/string_view_test.cpp
)

target_link_libraries(imogrify_tests PRIVATE
	Catch2::Catch2
	imogrify_core
)
