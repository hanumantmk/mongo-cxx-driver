cmake_minimum_required(VERSION 3.0)

project (mongo-cxx-driver)

include(ExternalProject)

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

ExternalProject_Add(libmongocxx
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/
    BUILD_COMMAND ${CMAKE_COMMAND}
    INSTALL_COMMAND ""
)

add_dependencies(libmongoc libmongocxx)
