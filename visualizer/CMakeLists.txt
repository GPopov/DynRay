add_executable(visualizer src/main.cpp)
target_link_libraries(visualizer SDL2-static)
add_subdirectory(test)