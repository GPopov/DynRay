#include "camera.hpp"
namespace DynRay
{
namespace Engine
{
glm::vec3 Camera::RasterToWorld(const glm::vec3 &rasterPoint, uint32_t width, uint32_t height) const
{
    glm::vec4 result;
    float aspectRatio = width / (float)height;
    result.x = (2.f * ((rasterPoint.x  + 0.5f) / width)- 1.f) * aspectRatio * glm::tan(m_VerticalFOV);
    result.y = (1.f - 2.f * ((rasterPoint.y + 0.5f) / height)) * glm::tan(m_VerticalFOV);
    result.z = rasterPoint.z;
    result.w = 1.f;

    return m_ToWorld * result;
}

glm::vec3 Camera::GeneratePrimaryRayDirection(uint32_t width, uint32_t height, uint32_t x, uint32_t y) const
{
    glm::vec3 rayDirection = RasterToWorld(glm::vec3(x, y, -1.f), width, height);
    rayDirection = glm::normalize(rayDirection);
    return rayDirection;
}
} // namespace Engine
} // namespace DynRay