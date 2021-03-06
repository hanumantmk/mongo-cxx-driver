cmake_minimum_required(VERSION 2.8.8)

project (libmongocxx)

include(ExternalProject)
include(GenerateExportHeader)

# Ensure that RPATH is used on OSX
set(CMAKE_MACOSX_RPATH 1)

set(WRAPPED_ABI_VERSION 1.0)

find_package(PkgConfig)
pkg_check_modules(LIBMONGOC libmongoc-${WRAPPED_ABI_VERSION})

link_directories(
    ${LIBMONGOC_LIBRARY_DIRS}
)

include_directories(
    ${LIBMONGOC_INCLUDE_DIRS}
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_custom_target(modernize
    clang-modernize
        -p ${CMAKE_BINARY_DIR}/compile_commands.json
        -include ${CMAKE_CURRENT_SOURCE_DIR}
        -exclude ${CMAKE_CURRENT_SOURCE_DIR}/test
        -format
    VERBATIM
)

add_custom_target(format
    perl -nle "/file/ or next; print ((split /: (.*)/)[1])" ${CMAKE_BINARY_DIR}/compile_commands.json |
    grep -v 'catch.hpp' |
    xargs clang-format -i
    VERBATIM
)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -ggdb3 -O0 -DMONGOCXX_DEBUG ${CMAKE_CXX_FLAGS}")
#set(CMAKE_EXE_LINKER_FLAGS "-lprofiler ${CMAKE_EXE_LINKER_FLAGS}")
#set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -ggdb3 -O2 -fsanitize=undefined,address ${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -ggdb3 -O2 ${CMAKE_CXX_FLAGS} -flto")

add_subdirectory(src)
add_subdirectory(test)
