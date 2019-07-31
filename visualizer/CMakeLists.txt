add_executable(visualizer src/main.cpp)
target_link_libraries(visualizer SDL2::SDL2-static SDLImage::SDLImage)
add_subdirectory(test)