#ifndef DYNRAY_CAMERA_HPP
#define DYNRAY_CAMERA_HPP
#include "glm/glm.hpp"
namespace DynRay
{
namespace Engine
{
    struct Camera
    {
        glm::vec3 RasterToWorld(const glm::vec3& rasterPoint, uint32_t width, uint32_t height) const;
        glm::vec4& GetEye() { return m_ToWorld[3];};
        const glm::vec4& GetEye() const { return m_ToWorld[3]; };
        glm::mat4x4 m_ToWorld = glm::mat4x4(1.f);
        float m_VerticalFOV = 1.0472f; //60 deg in rad default
    };
}
}

#endif //DYNRAY_CAMERA_HPP