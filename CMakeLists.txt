cmake_minimum_required(VERSION 3.8.0)
project(DynRay VERSION 0.1.0 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/CMake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/catch2-src/contrib)
add_subdirectory(extern)

enable_testing()

add_subdirectory(engine)
add_subdirectory(visualizer)