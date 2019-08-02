configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/Glm-CmakeLists.txt.in ${CMAKE_BINARY_DIR}/glm-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/glm-download
)

if (result)
    message("FATAL ERROR: Failed to download GLM")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/glm-download
)

if (result)
    message("FATAL ERROR: Failed to build glm")
endif()

add_subdirectory(${CMAKE_BINARY_DIR}/glm-src ${CMAKE_BINARY_DIR}/glm-build)