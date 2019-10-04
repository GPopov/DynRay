#include "SDLWrappers.h"
#include <vector>
struct SDL_Renderer;

namespace DynRay
{
namespace Visualizer
{
class Visualizer
{
   public:
   Visualizer(SDL_Renderer *renderer);   
   Visualizer(SDL_Renderer *renderer, uint32_t width, uint32_t height);
   uint32_t *GetPixelData() { return m_Pixels.data(); }

   int UpdateTexture();
   SDL_Texture *GetTexture();

private:
   uint32_t m_Width;
   uint32_t m_Height;
   std::vector<uint32_t> m_Pixels;
   DynRay::Visualizer::SDL_TexturePtr m_TargetTexture;
};
} //namespace Visualizer
} //namespace DynRay