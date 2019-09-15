#ifndef DYNRAY_CAMERA_HPP
#define DYNRAY_CAMERA_HPP
#include "glm/glm.hpp"
namespace DynRay
{
namespace Engine
{
    struct Camera
    {
        glm::vec4 RasterToCameraSpace(const glm::vec3& rasterPoint, uint32_t width, uint32_t height) const;
        glm::vec4 RasterToWorldSpace(const glm::vec3& rasterPoint, uint32_t width, uint32_t height) const;
        inline glm::vec4 GeneratePrimaryRayDirection(uint32_t width, uint32_t height, uint32_t x, uint32_t y) const;
        const glm::vec4& GetPosition() const {return m_ViewMatrix[3]; };
        void SetCameraMatrix(const glm::mat4x4& viewMatrix );

        glm::mat4x4 m_ViewMatrix = glm::mat4x4(1.f);
        glm::mat4x4 m_ToWorldMatrix = glm::inverse(glm::mat4x4(1.f));
        float m_VerticalFOV = 1.0472f; //60 deg in rad default
    };

    inline glm::vec4 Camera::GeneratePrimaryRayDirection(uint32_t width, uint32_t height, uint32_t x, uint32_t y) const
    {
        glm::vec4 cameraSpaceCoords = RasterToCameraSpace(glm::vec3(x, y, -1.f), width, height);
        cameraSpaceCoords.w = 0.f;
        glm::vec4 rayDirection = m_ViewMatrix * cameraSpaceCoords;
        rayDirection = glm::normalize(rayDirection);
        return rayDirection;
    }
}
}

#endif //DYNRAY_CAMERA_HPP