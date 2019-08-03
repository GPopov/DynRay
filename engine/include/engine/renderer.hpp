#ifndef DYNRAY_RENDERER
#define DYNRAY_RENDERER
#include <cstdint>

namespace DynRay
{
namespace Engine
{
    struct Scene;
    struct Camera;
    struct Renderer
    {
        static void Render(const Scene &scene, const Camera& camera, uint32_t width, uint32_t height, uint32_t *outBuffer);
    };
}
}
#endif //DYNRAY_RENDERER