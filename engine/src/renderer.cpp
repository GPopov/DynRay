#include "renderer.hpp"
#include "frame.hpp"
#include "object.hpp"
#include "renderoptions.hpp"
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

   inline void RenderSinglePixel_Impl(const Frame& frame, const glm::vec4 &rayOrigin, const RenderOptions& renderOptions, uint32_t *outBuffer, uint32_t x, uint32_t y)
   {
	   glm::vec4 rayDirection = frame.m_Camera.GeneratePrimaryRayDirection(renderOptions, x, y);

	   uint32_t pixelColor = 0;
	   HitRecord hitRecord = frame.m_Scene.Trace(rayOrigin, rayDirection, 0.f);
	   if (hitRecord.hitObject)
	   {
		   glm::vec4 color = hitRecord.hitObject->GetColorAt(hitRecord, frame.m_Scene);
		   pixelColor = QuantizeColor(color);
	   }

	   outBuffer[y * renderOptions.m_XResolution + x] = pixelColor;
   }

   void Renderer::Render(const Frame& frame, const RenderOptions& renderOptions, uint32_t *outBuffer)
   {
     const glm::vec4& rayOrigin = frame.m_Camera.GetPosition();
	 const uint32_t pixelsCount = renderOptions.m_XResolution * renderOptions.m_YResolution;

	 for (uint32_t pixelIdx = 0; pixelIdx < pixelsCount; ++pixelIdx)
	 {
		 uint32_t x = pixelIdx % renderOptions.m_XResolution;
		 uint32_t y = pixelIdx / renderOptions.m_XResolution;
		 RenderSinglePixel_Impl(frame, rayOrigin, renderOptions, outBuffer, x, y);

	 }
   }

   void Renderer::RenderSinglePixel(const Frame& frame, const RenderOptions& renderOptions, uint32_t *outBuffer, uint32_t x, uint32_t y)
   {
     const glm::vec4& rayOrigin = frame.m_Camera.GetPosition();
     
     RenderSinglePixel_Impl(frame, rayOrigin, renderOptions, outBuffer, x, y);
   }
}
}