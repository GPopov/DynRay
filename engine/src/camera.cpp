#include "camera.hpp"
namespace DynRay
{
namespace Engine
{

glm::vec4 Camera::RasterToCameraSpace(const glm::vec3 &rasterPoint, uint32_t width, uint32_t height) const
{
    glm::vec4 result;
    float aspectRatio = width / (float)height;
    result.x = (2.f * ((rasterPoint.x + 0.5f) / width) - 1.f) * aspectRatio * glm::tan(m_VerticalFOV);
    result.y = (1.f - 2.f * ((rasterPoint.y + 0.5f) / height)) * glm::tan(m_VerticalFOV);
    result.z = rasterPoint.z;
    result.w = 1.f;
    return result;
}

glm::vec4 Camera::RasterToWorldSpace(const glm::vec3 &rasterPoint, uint32_t width, uint32_t height) const
{
    return m_ToWorldMatrix * RasterToCameraSpace(rasterPoint, width, height);
}

glm::vec4 Camera::GeneratePrimaryRayDirection(uint32_t width, uint32_t height, uint32_t x, uint32_t y) const
{
    glm::vec4 cameraSpaceCoords = RasterToCameraSpace(glm::vec3(x, y, -1.f), width, height);
    cameraSpaceCoords.w = 0.f;
    glm::vec4 rayDirection = m_ViewMatrix * cameraSpaceCoords;
    rayDirection = glm::normalize(rayDirection);
    return rayDirection;
}

void Camera::SetCameraMatrix(const glm::mat4x4& viewMatrix)
{
    m_ViewMatrix = viewMatrix;
    m_ToWorldMatrix = glm::inverse(m_ViewMatrix);
}

} // namespace Engine
} // namespace DynRay