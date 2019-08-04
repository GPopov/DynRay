#include "object.hpp"
#include "glm/gtx/intersect.hpp"
#include "glm/gtc/constants.hpp"

namespace DynRay
{
namespace Engine
{
    glm::vec4 Sphere::GetNormal(const glm::vec4& point) const
    {
        return (point - m_Center) * (-1 / m_Radius);
    }
    glm::vec4 Sphere::GetColorAt(const glm::vec2& texCoords) const
    {
        constexpr float scale = 4.f;
        float pattern = (fmodf(texCoords.x * scale, 1.f) > 0.5f) ^ (fmodf(texCoords.y * scale, 1.f) > 0.5f);

        return glm::mix(m_Color, m_Color * 0.8f, pattern);
    }
    void Sphere::GetSurfaceDataAt(const glm::vec4 &point, glm::vec4 &outNormal, glm::vec2 &outTexCoords)
    {
        outNormal = GetNormal(point);
        
        outTexCoords.x = (1.f + glm::atan(outNormal.z, outNormal.x) * glm::one_over_pi<float>()) * 0.5f;
        outTexCoords.y = glm::acos(outNormal.y) * glm::one_over_pi<float>();
    }

    float Sphere::Intersect(const glm::vec4 &rayOrigin, const glm::vec4 &rayDirection) const
    {
        float distance = -1.f;
        bool result = glm::intersectRaySphere(rayOrigin, rayDirection, m_Center, m_Radius * m_Radius, distance);
        if (!result)
            distance = -1.f;

        return distance;
    }
}
}