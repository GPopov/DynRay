configure_file(${CMAKE_SOURCE_DIR}/cmake/Catch2-CMakeLists.txt.in ${CMAKE_BINARY_DIR}/catch2-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/catch2-download)

if(result)
    message("FATAL ERROR: Failed to download Catch2")

endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/catch2-download)

if(result)
    message("FATAL ERROR: Failed to build Catch2")
endif()

add_subdirectory(${CMAKE_BINARY_DIR}/catch2-src ${CMAKE_BINARY_DIR}/catch2-build)

add_executable(dynray_tests src/test_main.cpp src/test_fac.cpp src/test_mul.cpp)
target_link_libraries(dynray_tests Catch2::Catch2 DynRay::DynRay)


