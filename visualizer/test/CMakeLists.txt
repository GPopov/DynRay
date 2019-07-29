add_executable(visualizer_test src/test_main.cpp src/test_dummy.cpp)
target_link_libraries(visualizer_test Catch2::Catch2 DynRay::DynRay)