# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(IMOGRIFY_OS_LINUX)
    message(STATUS "Defining IMOGRIFY_OS_LINUX")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(IMOGRIFY_OS_WINDOWS)
    message(STATUS "Defining IMOGRIFY_OS_WINDOWS")
else ()
    message(WARNING "Unsupported operative system.")
endif ()
