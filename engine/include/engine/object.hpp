#ifndef DYNRAY_OBJECT_HPP
#define DYNRAY_OBJECT_HPP
#include "glm/glm.hpp"
namespace DynRay
{
namespace Engine
{
    struct Object
    {
        virtual ~Object() = default;
        virtual glm::vec3 GetNormal(const glm::vec3& point) const = 0;
        virtual glm::vec4 GetColorAt(const glm::vec3 &point) const = 0;
        virtual float Intersect(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection) const = 0;
    };

    struct Sphere : public Object
    {
        glm::vec3 GetNormal(const glm::vec3& point) const override;
        glm::vec4 GetColorAt(const glm::vec3 &point) const override;
        float Intersect(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection) const override;

        glm::vec4 m_Color;
        glm::vec3 m_Center;
        float m_Radius;
    };

} // namespace Engine
} // namespace DynRay
#endif //DYNRAY_OBJECT_HPP