#include "Visualizer.h"
#include "SDL.h"
namespace DynRay
{
namespace Visualizer
{
      
   Visualizer::Visualizer(SDL_Renderer* renderer)
   : Visualizer(renderer, 640, 480)
   {
   }

   Visualizer::Visualizer(SDL_Renderer *renderer, uint32_t width, uint32_t height)
      : m_Width(width)
      , m_Height(height)
      , m_Pixels(m_Width * m_Height)
   {
      m_TargetTexture = SDL_TexturePtr(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_Width, m_Height));
   }

   int Visualizer::UpdateTexture()
   {
      void* pixels;
      int pitch;
      SDL_LockTexture(m_TargetTexture.get(), nullptr, &pixels, &pitch);
      memcpy(pixels, m_Pixels.data(), pitch * m_Height);
      SDL_UnlockTexture(m_TargetTexture.get());

      return 0;
   }

   SDL_Texture* Visualizer::GetTexture()
   {
      return m_TargetTexture.get();
   }

} //namespace Visualizer
} //namespace DynRay