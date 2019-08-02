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
} // namespace Engine
} // namespace DynRay