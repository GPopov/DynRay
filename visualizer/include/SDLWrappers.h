#ifndef DYNRAY_SDL_WRAPPERS_H
#define DYNRAY_SDL_WRAPPERS_H

#include <memory>
#include <SDL.h>

#define DYNRAY_SDL_CUSTOM_DELETER(WrappedClass)     \
   struct SDL_##WrappedClass##Deleter               \
   {                                                \
      void operator()(SDL_##WrappedClass *wrapped)  \
      {                                             \
         SDL_Destroy##WrappedClass(wrapped);        \
      }                                             \
   };


namespace DynRay
{
   namespace Visualizer
   {
     DYNRAY_SDL_CUSTOM_DELETER(Renderer);
     DYNRAY_SDL_CUSTOM_DELETER(Texture);
     DYNRAY_SDL_CUSTOM_DELETER(Window);

     using SDL_RendererPtr = std::unique_ptr<SDL_Renderer, SDL_RendererDeleter>;
     using SDL_TexturePtr = std::unique_ptr<SDL_Texture, SDL_TextureDeleter>;
     using SDL_WindowPtr = std::unique_ptr<SDL_Window, SDL_WindowDeleter>;
   }
}

#endif //DYNRAY_SDL_WRAPPERS_H