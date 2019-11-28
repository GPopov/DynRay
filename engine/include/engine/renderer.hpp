#ifndef DYNRAY_RENDERER
#define DYNRAY_RENDERER
#include <cstdint>

namespace DynRay
{
namespace Engine
{
    struct Scene;
    struct Camera;
	struct RenderOptions;
    struct Renderer
    {
        static void Render(const Scene &scene, const Camera& camera, const RenderOptions& renderOptions, uint32_t *outBuffer);
		static void RenderSinglePixel(const Scene& scene, const Camera& camera, const RenderOptions& renderOptions, uint32_t* outBuffer, uint32_t x, uint32_t y);
	};
}
}
#endif //DYNRAY_RENDERER