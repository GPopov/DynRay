add_executable(engine_tests)
target_sources(engine_tests 
    PRIVATE
        src/test_main.cpp 
        src/test_camera.cpp
        src/test_normals.cpp
		src/test_trace.cpp
		src/test_light.cpp
)
add_custom_command(TARGET engine_tests POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               $<TARGET_FILE:DynRay::DynRay>              
               $<TARGET_FILE_DIR:engine_tests>)

include(CTest)
include(Catch)
enable_testing()
catch_discover_tests(engine_tests)

add_dependencies(engine_tests DynRay::DynRay)
target_link_libraries(engine_tests Catch2::Catch2 DynRay::DynRay glm)

target_compile_features(engine_tests 
	PRIVATE
		cxx_std_17
)


