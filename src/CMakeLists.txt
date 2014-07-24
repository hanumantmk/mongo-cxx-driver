add_library(mongocxx
    mongocxx.cpp
)

target_link_libraries(mongocxx
    ${LIBMONGOC_LIBRARIES}
)

add_dependencies(mongocxx
    libmongoc
)
