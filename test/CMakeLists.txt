enable_testing()

macro(test t)
    add_executable(test_${t} test_${t}.cpp)
    target_link_libraries(test_${t} mongocxx-static)
    add_test(test test_${t})
endmacro()

test(1)
test(2)
test(3)
test(4)
