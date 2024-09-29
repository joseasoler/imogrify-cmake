# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_executable(imogrify main.cpp)

target_link_libraries(imogrify PRIVATE
	Boost::filesystem
	Boost::nowide
	)

install(TARGETS imogrify RUNTIME)
