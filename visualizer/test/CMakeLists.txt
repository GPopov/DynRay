add_executable(visualizer_tests src/test_main.cpp src/test_dummy.cpp)
target_link_libraries(visualizer_tests Catch2::Catch2 DynRay::DynRay)


include(CTest)
include(Catch)
enable_testing()
catch_discover_tests(visualizer_tests)
add_custom_command(TARGET visualizer_tests POST_BUILD 
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:DynRay::DynRay>           
            $<TARGET_FILE_DIR:visualizer_tests>)