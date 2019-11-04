#include "renderer.hpp"
#include "scene.hpp"
#include "object.hpp"
#include "camera.hpp"
#include <limits>
namespace DynRay
{
namespace Engine
{
   namespace
   {
     uint32_t QuantizeColor(const glm::vec4& color)
     {
       constexpr glm::vec4 gammaPower = glm::vec4(1.f / 2.2f, 1.f / 2.2f, 1.f / 2.2f, 1.f / 2.2f);
       glm::vec4 clampedColor = glm::clamp(glm::pow(color, gammaPower), 0.f, 1.f);
       return uint32_t(clampedColor.a * 255) << 24 |
            uint32_t(clampedColor.r * 255) << 16 |
            uint32_t(clampedColor.g * 255) << 8 |
            uint32_t(clampedColor.b * 255);
     }
   }

   inline void RenderSinglePixel_Impl(const Scene &scene, const glm::vec4 &rayOrigin, const Camera &camera, uint32_t width, uint32_t height, uint32_t *outBuffer, uint32_t x, uint32_t y)
   {
	   glm::vec4 rayDirection = camera.GeneratePrimaryRayDirection(width, height, x, y);

	   uint32_t pixelColor = 0;
	   HitRecord hitRecord = scene.Trace(rayOrigin, rayDirection, 0.f);
	   if (hitRecord.hitObject)
	   {
		   glm::vec4 color = hitRecord.hitObject->GetColorAt(hitRecord, scene);
		   pixelColor = QuantizeColor(color);
	   }

	   outBuffer[y * width + x] = pixelColor;
   }

   void Renderer::Render(const Scene &scene, const Camera &camera, uint32_t width, uint32_t height, uint32_t *outBuffer)
   {
     const glm::vec4& rayOrigin = camera.GetPosition();
	 const uint32_t pixelsCount = width * height;

	 for (uint32_t pixelIdx = 0; pixelIdx < pixelsCount; ++pixelIdx)
	 {
		 uint32_t x = pixelIdx % width;
		 uint32_t y = pixelIdx / width;
		 RenderSinglePixel_Impl(scene, rayOrigin, camera, width, height, outBuffer, x, y);

	 }
   }

   void Renderer::RenderSinglePixel(const Scene &scene, const Camera &camera, uint32_t width, uint32_t height, uint32_t *outBuffer, uint32_t x, uint32_t y)
   {
     const glm::vec4& rayOrigin = camera.GetPosition();
     
     RenderSinglePixel_Impl(scene, rayOrigin, camera, width, height, outBuffer, x, y);
   }
}
}