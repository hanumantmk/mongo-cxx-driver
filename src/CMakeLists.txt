add_library(mongocxx-shared SHARED mongocxx_shared.cpp)
add_library(mongocxx-static STATIC mongocxx_static.cpp)

add_compiler_export_flags(LIBMONGOCXX_EXPORT_FLAGS)

set_target_properties(mongocxx-shared PROPERTIES
    DEFINE_SYMBOL LIBMONGOCXX_EXPORTS
    OUTPUT_NAME mongocxx
    COMPILE_FLAGS ${LIBMONGOCXX_EXPORT_FLAGS}
    LINK_FLAGS ${LIBMONGOCXX_EXPORT_FLAGS}
)

set_target_properties(mongocxx-static PROPERTIES
    DEFINE_SYMBOL LIBMONGOCXX_EXPORTS
    OUTPUT_NAME mongocxx
    COMPILE_FLAGS ${LIBMONGOCXX_EXPORT_FLAGS}
    LINK_FLAGS ${LIBMONGOCXX_EXPORT_FLAGS}
)

generate_export_header(mongocxx-shared
    EXPORT_MACRO_NAME LIBMONGOCXX_EXPORT
    EXPORT_FILE_NAME export.hpp
)

target_link_libraries(mongocxx-shared
    ${LIBMONGOC_LIBRARIES}
    mongocxx-bson
)

target_link_libraries(mongocxx-static
    ${LIBMONGOC_LIBRARIES}
    mongocxx-bson
)

add_subdirectory(bson)
