add_subdirectory(catch2)

set( SDL_STATIC ON CACHE BOOL "" FORCE )
set( SDL_SHARED OFF CACHE BOOL "" FORCE )
add_subdirectory(sdl2)
add_subdirectory(sdl2_image)
add_subdirectory(glm)