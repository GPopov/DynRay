add_executable(visualizer 
    src/main.cpp 
    src/Visualizer.h
    src/Visualizer.cpp
    include/SDLWrappers.h 
)

target_compile_features(visualizer PRIVATE cxx_alias_templates)
target_include_directories(visualizer PRIVATE include)
target_link_libraries(visualizer SDL2::SDL2-static SDLImage::SDLImage)
add_subdirectory(test)