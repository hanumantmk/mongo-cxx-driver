cmake_minimum_required(VERSION 2.8.6)

project (libmongocxx)

include(ExternalProject)

set(libmongoc_RELEASE 0.98.0)

ExternalProject_Add(libmongoc
    URL https://github.com/mongodb/mongo-c-driver/releases/download/${libmongoc_RELEASE}/mongo-c-driver-${libmongoc_RELEASE}.tar.gz
    DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/download/libmongoc-${libmongoc_RELEASE}
    SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/libmongoc/libmongoc-${libmongoc_RELEASE}
    CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/libmongoc/libmongoc-${libmongoc_RELEASE}/configure --prefix=<INSTALL_DIR> --without-documentation
    BUILD_COMMAND ${MAKE}
)

find_package(PkgConfig)

set(ENV{PKG_CONFIG_PATH} ${CMAKE_CURRENT_BINARY_DIR}/libmongoc-prefix/lib/pkgconfig)
pkg_check_modules(LIBMONGOC libmongoc-1.0)

link_directories(
    ${LIBMONGOC_LIBRARY_DIRS}
)

include_directories(
    ${LIBMONGOC_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -ggdb3 -O0 ${CMAKE_CXX_FLAGS}")

add_subdirectory(src)
add_subdirectory(tests)
