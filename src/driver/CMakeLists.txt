add_library(mongocxx-driver
    $<TARGET_OBJECTS:mongocxx-driver-base>
    $<TARGET_OBJECTS:mongocxx-driver-model>
    $<TARGET_OBJECTS:mongocxx-driver-options>
    $<TARGET_OBJECTS:mongocxx-driver-result>
    $<TARGET_OBJECTS:mongocxx-driver-util>
    libmongoc.cpp
)

if (BUILD_UNIT_TESTS)
    add_library(mocked-mongocxx-driver
        $<TARGET_OBJECTS:mongocxx-driver-base-mocked>
        $<TARGET_OBJECTS:mongocxx-driver-model>
        $<TARGET_OBJECTS:mongocxx-driver-options>
        $<TARGET_OBJECTS:mongocxx-driver-result>
        $<TARGET_OBJECTS:mongocxx-driver-util>
        libmongoc.cpp
    )
    set_target_properties(mocked-mongocxx-driver PROPERTIES
       COMPILE_FLAGS -DMONGOCXX_TESTING
    )
endif(BUILD_UNIT_TESTS)


add_subdirectory(base)
add_subdirectory(model)
add_subdirectory(options)
add_subdirectory(result)
add_subdirectory(util)
