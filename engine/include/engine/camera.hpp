#ifndef DYNRAY_CAMERA_HPP
#define DYNRAY_CAMERA_HPP
#include "glm/glm.hpp"
namespace DynRay
{
namespace Engine
{
    struct Camera
    {
		inline glm::vec4 RasterToCameraSpace(const glm::vec3& rasterPoint, uint32_t width, uint32_t height) const;
		inline glm::vec4 RasterToWorldSpace(const glm::vec3& rasterPoint, uint32_t width, uint32_t height) const;
		inline glm::vec4 GeneratePrimaryRayDirection(uint32_t width, uint32_t height, uint32_t x, uint32_t y) const;
		inline void SetCameraMatrix(const glm::mat4x4& viewMatrix);
		inline const glm::vec4& GetPosition() const {return m_ViewMatrix[3]; };

        glm::mat4x4 m_ViewMatrix = glm::mat4x4(1.f);
        glm::mat4x4 m_ToWorldMatrix = glm::inverse(glm::mat4x4(1.f));
        float m_VerticalFOV = 1.0472f; //60 deg in rad default
    };



	inline glm::vec4 Camera::RasterToCameraSpace(const glm::vec3& rasterPoint, uint32_t width, uint32_t height) const
	{
		glm::vec4 result;
		float aspectRatio = width / (float)height;
		result.x = (2.f * ((rasterPoint.x + 0.5f) / width) - 1.f) * aspectRatio * glm::tan(m_VerticalFOV);
		result.y = (1.f - 2.f * ((rasterPoint.y + 0.5f) / height)) * glm::tan(m_VerticalFOV);
		result.z = rasterPoint.z;
		result.w = 1.f;
		return result;
	}

	inline glm::vec4 Camera::RasterToWorldSpace(const glm::vec3& rasterPoint, uint32_t width, uint32_t height) const
	{
		return m_ToWorldMatrix * RasterToCameraSpace(rasterPoint, width, height);
	}

	inline glm::vec4 Camera::GeneratePrimaryRayDirection(uint32_t width, uint32_t height, uint32_t x, uint32_t y) const
	{
		glm::vec4 cameraSpaceCoords = RasterToCameraSpace(glm::vec3(x, y, -1.f), width, height);
		cameraSpaceCoords.w = 0.f;
		glm::vec4 rayDirection = m_ViewMatrix * cameraSpaceCoords;
		rayDirection = glm::normalize(rayDirection);
		return rayDirection;
	}

	inline void Camera::SetCameraMatrix(const glm::mat4x4& viewMatrix)
	{
		m_ViewMatrix = viewMatrix;
		m_ToWorldMatrix = glm::inverse(m_ViewMatrix);
	}
}
}

#endif //DYNRAY_CAMERA_HPP