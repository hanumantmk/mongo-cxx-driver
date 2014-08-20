file (GLOB mongocxx-driver-util_headers *.hpp)
file (GLOB mongocxx-driver-util_sources *.cpp)

add_library(mongocxx-driver-util OBJECT ${mongocxx-driver-util_sources})
