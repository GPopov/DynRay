add_executable(engine_tests)
target_sources(engine_tests 
    PRIVATE
        src/test_main.cpp 
        src/test_camera.cpp
)
target_link_libraries(engine_tests Catch2::Catch2 DynRay::DynRay glm)


