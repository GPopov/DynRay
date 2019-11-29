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

		inline void RenderSinglePixel_impl(const Scene& scene, const glm::vec4& rayOrigin, const glm::vec4& rayDirection, const RenderOptions& renderOptions, uint32_t* outBuffer, uint32_t x, uint32_t y)
		{
			uint32_t pixelColor = 0;
			const Object* closestObject = nullptr;
			float hitDistance = scene.Trace(rayOrigin, rayDirection, closestObject, 0.f);
			if (closestObject)
			{
				glm::vec4 intersectionPoint = rayOrigin + rayDirection * hitDistance;
				glm::vec4 color = closestObject->GetColorAt(intersectionPoint, scene);

				pixelColor = QuantizeColor(color);
			}

			outBuffer[y * renderOptions.m_XResolution + x] = pixelColor;
		}
    }
    void Renderer::Render(const Frame& frame, const RenderOptions& renderOptions, uint32_t *outBuffer)
    {
        const glm::vec4& rayOrigin = frame.m_Camera.GetPosition();
        for (uint32_t y = 0; y < renderOptions.m_YResolution; ++y)
        {
			for (uint32_t x = 0; x < renderOptions.m_XResolution; ++x)
			{
				const glm::vec4 rayDirection = frame.m_Camera.GeneratePrimaryRayDirection(renderOptions, x, y);
				RenderSinglePixel_impl(frame.m_Scene, rayOrigin, rayDirection, renderOptions, outBuffer, x, y);
			}
        }
    }

	void Renderer::RenderSinglePixel(const Frame& frame, const RenderOptions& renderOptions, uint32_t *outBuffer, uint32_t x, uint32_t y)
	{
		const glm::vec4& rayOrigin = frame.m_Camera.GetPosition();
		const glm::vec4 rayDirection = frame.m_Camera.GeneratePrimaryRayDirection(renderOptions, x, y);
		RenderSinglePixel_impl(frame.m_Scene, rayOrigin, rayDirection, renderOptions, outBuffer, x, y);
	}
}
}