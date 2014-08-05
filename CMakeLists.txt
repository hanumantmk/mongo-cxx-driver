cmake_minimum_required(VERSION 2.8.6)

project (mongo-cxx-driver)

include(ExternalProject)

set(libmongoc_ABI 1.0)
set(libmongoc_RELEASE 0.98.0)
set(libmongoc_FLAGS --prefix=<INSTALL_DIR> --without-documentation)
set(libmongoc_URL https://github.com/mongodb/mongo-c-driver/releases/download)

ExternalProject_Add(libmongoc
    URL ${libmongoc_URL}/${libmongoc_RELEASE}/mongo-c-driver-${libmongoc_RELEASE}.tar.gz
    DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/download/
    SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/libmongoc/${libmongoc_RELEASE}
    CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/libmongoc/${libmongoc_RELEASE}/configure ${libmongoc_FLAGS}
    BUILD_COMMAND ${MAKE}
)

add_dependencies(libmongocxx
    libmongoc
)

find_package(PkgConfig)
set(ENV{PKG_CONFIG_PATH} ${CMAKE_INSTALL_PREFIX}/libmongoc-prefix/lib/pkgconfig)
pkg_check_modules(LIBMONGOC REQUIRED libmongoc-${libmongoc_ABI})

link_directories(
    ${LIBMONGOC_LIBRARY_DIRS}
)

include_directories(
    ${LIBMONGOC_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -ggdb3 -O0 ${CMAKE_CXX_FLAGS}")

add_subdirectory(src)
add_subdirectory(test)
