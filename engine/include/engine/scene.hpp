#ifndef DYNRAY_SCENE_HPP
#define DYNRAY_SCENE_HPP
#include <vector>
#include <memory>
#include "object.hpp"
#include "light.hpp"
namespace DynRay
{
namespace Engine
{
    struct Scene
    {
        template <typename ObjectType>
        void AddObject(ObjectType&& object);

        inline float Trace(const glm::vec4& rayOrigin, const glm::vec4& rayDirection, const Object*& hitObject, float sqrMin, float sqrMax = std::numeric_limits<float>::infinity()) const;

        template <typename ObjectContainer>
        inline static float Trace_Impl(const ObjectContainer &objects, const glm::vec4 &rayOrigin, const glm::vec4 &rayDirection, const Object *&hitObject, float sqrMin, float sqrMax);
        

        Sphere m_Spheres[100];
        uint32_t m_SphereCount = 0;
        std::vector<Plane> m_Planes;
        std::vector<OmniLight> m_Omnis;	
    };

    inline float Scene::Trace(const glm::vec4 &rayOrigin, const glm::vec4 &rayDirection, const Object *&hitObject, float sqrMin, float sqrMax) const
    {
        float closestSph = Scene::Trace_Impl(m_Spheres, rayOrigin, rayDirection, hitObject, sqrMin, sqrMax);
        float closestPlane = Scene::Trace_Impl(m_Planes, rayOrigin, rayDirection, hitObject, closestSph * closestSph, sqrMax);
        return std::min(closestSph, closestPlane)
    }

    template <typename ObjectContainer>
    inline float Scene::Trace_Impl(const ObjectContainer &objects, const glm::vec4 &rayOrigin, const glm::vec4 &rayDirection, const Object *&hitObject, float sqrMin, float sqrMax)
    {
        float minSqrDistance = sqrMax;
        float minDistance = std::numeric_limits<float>::infinity();

        for (const auto &object : objects)
        {
            float distance = object.Intersect(rayOrigin, rayDirection);
            float sqrDistance = distance * distance;
            if (distance > 0.f &&
                sqrDistance > sqrMin &&
                sqrDistance < minSqrDistance)
            {
                minSqrDistance = sqrDistance;
                minDistance = distance;
                hitObject = &object;
            }
        }
        return minDistance;
    }
} // namespace Engine   
} // namespace DynRay

#endif //DYNRAY_SCENE_HPP