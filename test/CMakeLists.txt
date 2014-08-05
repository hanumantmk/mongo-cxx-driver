ExternalProject_Add(gtest
    URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
    DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/download/
    SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/gtest/
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    INSTALL_COMMAND ""
)

enable_testing()

macro(test t)
    add_executable(test_${t} test_${t}.cpp)
    target_link_libraries(test_${t} mongocxx)
    add_test(test test_${t})
endmacro()

test(1)
test(2)
test(3)
