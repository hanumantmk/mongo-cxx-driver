set(libmongoc_ABI 1.0)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -ggdb3 -O0 ${CMAKE_CXX_FLAGS}")

find_package(PkgConfig)
set(ENV{PKG_CONFIG_PATH} ${CMAKE_INSTALL_PREFIX}/libmongoc-prefix/lib/pkgconfig)
pkg_check_modules(LIBMONGOC libmongoc-${libmongoc_ABI})

link_directories(
    ${LIBMONGOC_LIBRARY_DIRS}
)

include_directories(
    ${LIBMONGOC_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)


add_library(mongocxx
    bson/document.cpp
    driver/base/bulk.cpp
    driver/base/client.cpp
    driver/base/collection.cpp
    driver/base/cursor.cpp
    driver/base/database.cpp
    driver/model/find.cpp
    driver/model/insert.cpp
    driver/request/insert.cpp
    driver/result/write.cpp
    driver/util/libbson.cpp
    driver/util/optional.cpp
)

target_link_libraries(mongocxx
    ${LIBMONGOC_LIBRARIES}
)

add_dependencies(mongocxx
    libmongoc
)

add_subdirectory(test)
