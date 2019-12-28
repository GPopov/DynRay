#include "camera.hpp"
namespace DynRay
{
namespace Engine
{

glm::vec4 Camera::RasterToCameraSpace(const glm::vec3 &rasterPoint, const RenderOptions& renderOptions) const
{
   glm::vec4 result;
   const float aspectRatio = renderOptions.Aspect();
   const float scale = glm::tan(m_VerticalFOV * 0.5f);
   result.x = (2.f * ((rasterPoint.x + 0.5f) / renderOptions.m_XResolution) - 1.f) * aspectRatio * scale;
   result.y = (1.f - 2.f * ((rasterPoint.y + 0.5f) / renderOptions.m_YResolution)) * scale;
   result.z = rasterPoint.z;
   result.w = 1.f;
   return result;
}

glm::vec4 Camera::RasterToWorldSpace(const glm::vec3 &rasterPoint, const RenderOptions& renderOptions) const
{
   return m_ToWorldMatrix * RasterToCameraSpace(rasterPoint, renderOptions);
}

void Camera::SetCameraMatrix(const glm::mat4x4& viewMatrix)
{
   m_ViewMatrix = viewMatrix;
   m_ToWorldMatrix = glm::inverse(m_ViewMatrix);
}

} // namespace Engine
} // namespace DynRay