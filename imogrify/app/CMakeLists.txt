# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_executable(imogrify main.cpp)

target_compile_options(imogrify PRIVATE ${IMOGRIFY_CPP_WARNING_FLAGS})

target_link_libraries(imogrify PRIVATE
	imogrify_core
)

install(TARGETS imogrify RUNTIME)
