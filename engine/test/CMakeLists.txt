add_executable(engine_tests src/test_main.cpp src/test_dummy.cpp)
target_link_libraries(engine_tests Catch2::Catch2 DynRay::DynRay)


