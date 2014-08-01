add_library(mongocxx
    mongocxx.cpp
    base/database.cpp
    base/cursor.cpp
    base/collection.cpp
    base/client.cpp
    models/find.cpp
    util/libbson.cpp
    util/optional.cpp
)

target_link_libraries(mongocxx
    ${LIBMONGOC_LIBRARIES}
)

add_dependencies(mongocxx
    libmongoc
)
