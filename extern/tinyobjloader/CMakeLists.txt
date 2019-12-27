configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/tinyobjloader-CMakeLists.txt.in
               ${CMAKE_BINARY_DIR}/tinyobjloader-download/CMakeLists.txt)
execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tinyobjloader-download)

if(result)
  message("FATAL ERROR: Failed to download tinyobjloader")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tinyobjloader-download)

if(result)
  message("FATAL ERROR: Failed to build tinyobjloader")
endif()

add_subdirectory(${CMAKE_BINARY_DIR}/tinyobjloader-src
                 ${CMAKE_BINARY_DIR}/tinyobjloader-build)
