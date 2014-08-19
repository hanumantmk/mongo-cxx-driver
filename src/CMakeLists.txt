# TODO: use GLOB
add_library(mongocxx SHARED
    bson/builder.cpp
    bson/document.cpp
    bson/string_or_literal.cpp
    bson/util/itoa.cpp
    driver/libmongoc.cpp
    driver/base/client.cpp
    driver/base/collection.cpp
    driver/base/cursor.cpp
    driver/base/database.cpp
    driver/base/options.cpp
    driver/model/bulk.cpp
    driver/model/find.cpp
    driver/model/insert.cpp
    driver/request/insert.cpp
    driver/result/write.cpp
    driver/util/libbson.cpp
    driver/util/optional.cpp
)

set_target_properties(mongocxx PROPERTIES
    DEFINE_SYMBOL LIBMONGOCXX_EXPORTS
)

if (BUILD_SHARED_LIBS)
    add_compiler_export_flags(LIBMONGOCXX_EXPORT_FLAGS)
    set_target_properties(mongocxx PROPERTIES COMPILE_FLAGS ${LIBMONGOCXX_EXPORT_FLAGS})
    set_target_properties(mongocxx PROPERTIES LINK_FLAGS ${LIBMONGOCXX_EXPORT_FLAGS})
endif()

generate_export_header(mongocxx
    EXPORT_MACRO_NAME LIBMONGOCXX_EXPORT
)

target_link_libraries(mongocxx
    ${LIBMONGOC_LIBRARIES}
)
