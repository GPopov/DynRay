configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/Benchmark-CMakeLists.txt.in ${CMAKE_BINARY_DIR}/benchmark-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/benchmark-download)

if(result)
    message("FATAL ERROR: Failed to download Benchmark")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/benchmark-download)

if(result)
    message("FATAL ERROR: Failed to build Benchmark")
endif()
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Enable building the unit tests which depend on gtest" FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Enable testing of the benchmark library." FORCE)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory(${CMAKE_BINARY_DIR}/benchmark-src ${CMAKE_BINARY_DIR}/benchmark-build)