add_library(mongocxx-driver
    $<TARGET_OBJECTS:mongocxx-driver-base>
    #$<TARGET_OBJECTS:mongocxx-driver-model>
    $<TARGET_OBJECTS:mongocxx-driver-options>
    $<TARGET_OBJECTS:mongocxx-driver-result>
    $<TARGET_OBJECTS:mongocxx-driver-util>
    libmongoc.cpp
)

add_subdirectory(base)
add_subdirectory(model)
add_subdirectory(options)
add_subdirectory(result)
add_subdirectory(util)
