#ifndef DYNRAY_CAMERA_HPP
#define DYNRAY_CAMERA_HPP
#include "glm/glm.hpp"
#include "renderoptions.hpp"
namespace DynRay
{
namespace Engine
{
    struct Camera
    {
      glm::vec4 RasterToCameraSpace(const glm::vec3& rasterPoint, const RenderOptions& renderOptions) const;
      glm::vec4 RasterToWorldSpace(const glm::vec3& rasterPoint, const RenderOptions& renderOptions) const;
      inline glm::vec4 GeneratePrimaryRayDirection(const RenderOptions& renderOptions, uint32_t x, uint32_t y) const;
      const glm::vec4& GetPosition() const {return m_ToWorldMatrix[3]; };
      void SetCameraMatrix(const glm::mat4x4& viewMatrix );

        glm::mat4x4 m_ViewMatrix = glm::mat4x4(1.f);
        glm::mat4x4 m_ToWorldMatrix = glm::inverse(glm::mat4x4(1.f));
        float m_VerticalFOV = 1.0472f; //60 deg in rad default
    };

	inline glm::vec4 Camera::GeneratePrimaryRayDirection(const RenderOptions& renderOptions, uint32_t x, uint32_t y) const
	{

        float scale = glm::tan(m_VerticalFOV * 0.5f);
        float aspect = renderOptions.Aspect();
        float _x = (2 * (x + 0.5f) / (float)renderOptions.m_XResolution - 1) * aspect * scale;
        float _y = (1 - 2 * (y + 0.5f) / (float)renderOptions.m_YResolution) * scale;
        auto dir = m_ToWorldMatrix * glm::vec4(_x, _y, -1.f, 0.f);
        dir = glm::normalize(dir);
		return dir;
	}
}
}

#endif //DYNRAY_CAMERA_HPP