add_executable(visualizer_test src/test_main.cpp src/test_dummy.cpp)
target_link_libraries(visualizer_test Catch2::Catch2 DynRay::DynRay)

add_custom_command(TARGET visualizer_test POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               $<TARGET_FILE:DynRay::DynRay>              
               $<TARGET_FILE_DIR:visualizer_test>)