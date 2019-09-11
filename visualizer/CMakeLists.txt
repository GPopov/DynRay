add_executable(visualizer 
    src/main.cpp 
    src/Visualizer.h
    src/Visualizer.cpp
    include/SDLWrappers.h 
)

target_compile_features(visualizer PRIVATE cxx_alias_templates cxx_std_17)
target_include_directories(visualizer PRIVATE include)
target_link_libraries(visualizer DynRay::DynRay SDL2::SDL2-static SDL2::SDL2main SDLImage::SDLImage glm)

add_subdirectory_with_folder("tests" test)

add_custom_command(TARGET visualizer POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               $<TARGET_FILE:DynRay::DynRay>              
               $<TARGET_FILE_DIR:visualizer>)