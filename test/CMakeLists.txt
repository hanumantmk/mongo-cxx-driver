enable_testing()

ExternalProject_Add(
    googletest
    URL http://googletest.googlecode.com/files/gtest-1.7.0.zip
    DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/download
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    INSTALL_COMMAND ""
)

macro(test t)
    add_executable(test_${t} test_${t}.cpp)
    target_link_libraries(test_${t}
        ${LIBMONGOC_LIBRARIES}
        mongocxx
    )
    add_test(test test_${t})
endmacro()

link_directories(
    ${LIBMONGOC_LIBRARY_DIRS}
)

include_directories(
    ${LIBMONGOC_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
)

test(1)
test(2)
test(3)
