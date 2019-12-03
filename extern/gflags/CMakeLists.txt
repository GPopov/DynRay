configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/gflags-CMakeLists.txt.in
               ${CMAKE_BINARY_DIR}/gflags-download/CMakeLists.txt)
execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gflags-download)

if(result)
  message("FATAL ERROR: Failed to download gflags")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gflags-download)

if(result)
  message("FATAL ERROR: Failed to build gflags")
endif()

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory(${CMAKE_BINARY_DIR}/gflags-src
                 ${CMAKE_BINARY_DIR}/gflags-build)
