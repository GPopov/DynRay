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
        float m_VerticalFOV = glm::radians(90.f);
    };

	inline glm::vec4 Camera::GeneratePrimaryRayDirection(const RenderOptions& renderOptions, uint32_t x, uint32_t y) const
	{
        glm::vec4 cameraSpaceCoords = RasterToCameraSpace({ x,y,-1.f }, renderOptions);
        cameraSpaceCoords.w = 0.f;
        auto rayDirection = m_ToWorldMatrix * cameraSpaceCoords;
        rayDirection = glm::normalize(rayDirection);;
		return rayDirection;
	}
}
}

#endif //DYNRAY_CAMERA_HPP