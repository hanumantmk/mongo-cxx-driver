file (GLOB mongocxx-driver-operation_headers *.hpp)
file (GLOB mongocxx-driver-operation_sources *.cpp)

add_library(mongocxx-driver-operation OBJECT ${mongocxx-driver-operation_sources})
