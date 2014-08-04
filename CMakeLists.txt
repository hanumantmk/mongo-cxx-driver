cmake_minimum_required(VERSION 2.8.7)

project (libmongocxx)

include(ExternalProject)

set(libmongoc_RELEASE 0.98.0)
set(github_url https://github.com/mongodb/mongo-c-driver/releases/download)

ExternalProject_Add(libmongoc
    URL ${github_url}/${libmongoc_RELEASE}/mongo-c-driver-${libmongoc_RELEASE}.tar.gz
    DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/download
    SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/libmongoc/libmongoc-${libmongoc_RELEASE}
    CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/libmongoc/libmongoc-${libmongoc_RELEASE}/configure --prefix=<INSTALL_DIR> --without-documentation
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    BUILD_COMMAND ${MAKE}
)

find_package(PkgConfig)

set(ENV{PKG_CONFIG_PATH} ${CMAKE_CURRENT_BINARY_DIR}/libmongoc-prefix/lib/pkgconfig)
pkg_check_modules(LIBMONGOC libmongoc-1.0)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -ggdb3 -O0 ${CMAKE_CXX_FLAGS}")

add_subdirectory(src)
add_subdirectory(test)
