#include "object.hpp"
#include "glm/gtx/intersect.hpp"

namespace DynRay
{
namespace Engine
{
    glm::vec3 Sphere::GetNormal(const glm::vec3& point) const
    {
        return (point - m_Center) * (-1 / m_Radius);
    }
    glm::vec4 Sphere::GetColorAt(const glm::vec3& point) const
    {
        return m_Color;
    }

    float Sphere::Intersect(const glm::vec3& rayOrigin, const glm::vec3& rayDirection) const
    {
        float distance = -1.f;
        bool result = glm::intersectRaySphere(rayOrigin, rayDirection, m_Center, m_Radius * m_Radius, distance);
        if (!result)
            distance = -1.f;

        return distance;
    }
}
}