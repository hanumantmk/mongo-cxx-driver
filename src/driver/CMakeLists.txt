add_library(mongocxx-driver
    $<TARGET_OBJECTS:mongocxx-driver-base>
    $<TARGET_OBJECTS:mongocxx-driver-model>
    $<TARGET_OBJECTS:mongocxx-driver-options>
    $<TARGET_OBJECTS:mongocxx-driver-result>
    $<TARGET_OBJECTS:mongocxx-driver-util>
    libmongoc.cpp
)

if (BUILD_UNIT_TESTS)
    add_library(mongocxx-mock_symbols STATIC libmongoc.cpp)
    set_target_properties(mongocxx-mock_symbols PROPERTIES
       COMPILE_FLAGS -DMONGOCXX_TESTING)
    target_link_libraries(mongocxx-mock_symbols ${LIBMONGOC_LIBRARIES})
endif(BUILD_UNIT_TESTS)


add_subdirectory(base)
add_subdirectory(model)
add_subdirectory(options)
add_subdirectory(result)
add_subdirectory(util)
