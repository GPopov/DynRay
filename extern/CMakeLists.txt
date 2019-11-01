add_subdirectory_with_folder("extern/catch2" catch2)

set( SDL_STATIC ON CACHE BOOL "" FORCE )
set( SDL_SHARED OFF CACHE BOOL "" FORCE )
add_subdirectory_with_folder("extern/sdl2" sdl2)
add_subdirectory_with_folder("extern/sdl2_image" sdl2_image)
add_subdirectory_with_folder("extern/glm" glm)
add_subdirectory_with_folder("extern/benchmark" benchmark)