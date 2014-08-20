file (GLOB mongocxx-driver-base_headers *.hpp)
file (GLOB mongocxx-driver-base_sources *.cpp)

add_library(mongocxx-driver-base OBJECT ${mongocxx-driver-base_sources})
