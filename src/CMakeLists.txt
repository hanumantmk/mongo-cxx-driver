link_directories(
    ${LIBMONGOC_LIBRARY_DIRS}
)

include_directories(
    ${LIBMONGOC_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(mongocxx
    mongocxx.cpp
    base/bulk.cpp
    base/database.cpp
    base/cursor.cpp
    base/collection.cpp
    base/client.cpp
    bson/document.cpp
    models/find.cpp
    models/insert.cpp
    models/insert_request.cpp
    results/write.cpp
    util/libbson.cpp
    util/optional.cpp
)

target_link_libraries(mongocxx
    ${LIBMONGOC_LIBRARIES}
)

add_dependencies(mongocxx
    libmongoc
)
