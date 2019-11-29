#ifndef DYNRAY_RENDERER
#define DYNRAY_RENDERER
#include <cstdint>

namespace DynRay
{
namespace Engine
{
	struct Frame;
	struct RenderOptions;
    struct Renderer
    {
        static void Render(const Frame& frame, const RenderOptions& renderOptions, uint32_t *outBuffer);
		static void RenderSinglePixel(const Frame& frame, const RenderOptions& renderOptions, uint32_t* outBuffer, uint32_t x, uint32_t y);
	};
}
}
#endif //DYNRAY_RENDERER