CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(SDL_image VERSION 2.0.1)

set(ENABLE_DEFS "")
set(LINK_LIBS SDL2-static)
set(INCLUDE_DIRS ${SDL2_INCLUDE_DIR})

option(ENABLE_BMP "ENABLE_BMP" ON)
option(ENABLE_GIF "ENABLE_GIF" ON)
option(ENABLE_JPG "ENABLE_JPG" OFF)
option(ENABLE_LBM "ENABLE_LBM" ON)
option(ENABLE_PCX "ENABLE_PCX" ON)
option(ENABLE_PNG "ENABLE_PNG" OFF)
option(ENABLE_PNM "ENABLE_PNM" ON)
option(ENABLE_TGA "ENABLE_TGA" ON)
option(ENABLE_TIF "ENABLE_TIF" OFF)
option(ENABLE_WEBP "ENABLE_WEBP" OFF) # BROKEN
option(ENABLE_XCF "ENABLE_XCF" ON)
option(ENABLE_XPM "ENABLE_XPM" ON)
option(ENABLE_XV "ENABLE_XV" ON)

if(ENABLE_BMP)
    set(ENABLE_DEFS "${ENABLE_DEFS}" LOAD_BMP)
endif()

if(ENABLE_GIF)
    set(ENABLE_DEFS "${ENABLE_DEFS}" LOAD_GIF)
endif()

if(ENABLE_JPG)
    set(ENABLE_DEFS "${ENABLE_DEFS}" LOAD_JPG)
    find_package(JPEG REQUIRED)
    set(LINK_LIBS "${LINK_LIBS}" "${JPEG_LIBRARIES}")
    set(INCLUDE_DIRS "${INCLUDE_DIRS}" "${JPEG_INCLUDE_DIRS}")
endif()

if(ENABLE_LBM)
    set(ENABLE_DEFS "${ENABLE_DEFS}" LOAD_LBM)
endif()

if(ENABLE_PCX)
    set(ENABLE_DEFS "${ENABLE_DEFS}" LOAD_PCX)
endif()

if(ENABLE_PNG)
    set(ENABLE_DEFS "${ENABLE_DEFS}" LOAD_PNG)
    find_package(PNG REQUIRED)
    set(LINK_LIBS "${LINK_LIBS}" "${PNG_LIBRARIES}")
    set(INCLUDE_DIRS "${INCLUDE_DIRS}" "${PNG_INCLUDE_DIRS}")
endif()

if(ENABLE_PNM)
    set(ENABLE_DEFS "${ENABLE_DEFS}" LOAD_PNM)
endif()

if(ENABLE_TGA)
    set(ENABLE_DEFS "${ENABLE_DEFS}" LOAD_TGA)
endif()

if(ENABLE_TIF)
    set(ENABLE_DEFS "${ENABLE_DEFS}" LOAD_TIF)
    find_package(TIFF REQUIRED)
    set(LINK_LIBS "${LINK_LIBS}" "${TIFF_LIBRARIES}")
    set(INCLUDE_DIRS "${INCLUDE_DIRS}" "${TIFF_INCLUDE_DIRS}")
endif()

if(ENABLE_WEBP)
    set(ENABLE_DEFS "${ENABLE_DEFS}" LOAD_WEBP)
    find_package(WebP REQUIRED) # BROKEN, debian doesn't install the cmake config files, so find_package will fail
    set(LINK_LIBS "${LINK_LIBS}" "${WebP_LIBRARIES}")
    set(INCLUDE_DIRS "${INCLUDE_DIRS}" "${WebP_INCLUDE_DIRS}")
endif()

if(ENABLE_XCF)
    set(ENABLE_DEFS "${ENABLE_DEFS}" LOAD_XCF)
endif()

if(ENABLE_XV)
    set(ENABLE_DEFS "${ENABLE_DEFS}" LOAD_XV)
endif()

set(SRC_C_FILES
    src/IMG.c
    src/IMG_bmp.c
    src/IMG_gif.c
    src/IMG_jpg.c
    src/IMG_lbm.c
    src/IMG_pcx.c
    src/IMG_png.c
    src/IMG_pnm.c
    src/IMG_svg.c
    src/IMG_tga.c
    src/IMG_tif.c
    src/IMG_webp.c
    src/IMG_xcf.c
    src/IMG_xpm.c
    src/IMG_xv.c
    src/IMG_xxx.c
)

set(SRC_H_FILES  
    include/SDL_image.h
)

set(SRC_FILES ${SRC_C_FILES} ${SRC_H_FILES})

add_library(SDL_image STATIC ${SRC_FILES})
add_library (SDLImage::SDLImage ALIAS SDL_image)
target_link_libraries(SDL_image ${LINK_LIBS})
target_compile_definitions(SDL_image PUBLIC SDL_IMAGE_USE_COMMON_BACKEND)
target_include_directories(SDL_image PRIVATE {$INCLUDE_DIRS})
target_include_directories(SDL_image PRIVATE external/miniz external/nanosvg)
target_include_directories(SDL_image PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" $<INSTALL_INTERFACE:include>)

target_compile_definitions(SDL_image PUBLIC "${ENABLE_DEFS}")