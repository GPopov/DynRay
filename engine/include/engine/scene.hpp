#ifndef DYNRAY_SCENE_HPP
#define DYNRAY_SCENE_HPP
#include <vector>
#include <memory>
#include <algorithm>
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

        enum class TraceMode
        {
            SingleHit,
            Closest
        };

        template<TraceMode traceMode = TraceMode::Closest>
        inline HitRecord Trace(const glm::vec4& rayOrigin, const glm::vec4& rayDirection, float minDistance, float maxDistance = std::numeric_limits<float>::infinity()) const;

        template <typename ObjectContainer, TraceMode traceMode>
        inline static void Trace_Impl(const ObjectContainer& objects, const glm::vec4& rayOrigin, const glm::vec4& rayDirection, float minDistance, HitRecord& hitRecord);


        std::vector<Sphere> m_Spheres;
        std::vector<Plane> m_Planes;
        std::vector<OmniLight> m_Omnis;
    };

    template<Scene::TraceMode traceMode>
    inline HitRecord Scene::Trace(const glm::vec4& rayOrigin, const glm::vec4& rayDirection, float minDistance, float maxDistance) const
    {
        HitRecord hitRecord;
        hitRecord.t = maxDistance;
        hitRecord.minDistance = minDistance;

        Scene::Trace_Impl<decltype(m_Spheres), traceMode>(m_Spheres, rayOrigin, rayDirection, minDistance, hitRecord);
        Scene::Trace_Impl<decltype(m_Planes), traceMode>(m_Planes, rayOrigin, rayDirection, minDistance, hitRecord);

        return hitRecord;
    }

    template <typename ObjectContainer, Scene::TraceMode traceMode>
    inline void Scene::Trace_Impl(const ObjectContainer& objects, const glm::vec4& rayOrigin, const glm::vec4& rayDirection, float minDistance, HitRecord& hitRecord)
    {
        for (const auto& object : objects)
        {
            if constexpr (traceMode == TraceMode::SingleHit)
            {
                if (hitRecord.hitObject)
                    return;
            }
            object.Intersect(rayOrigin, rayDirection, hitRecord);
        }

        if (hitRecord.hitObject)
        {
            hitRecord.hitPos = rayOrigin + rayDirection * hitRecord.t;
            hitRecord.hitObject->ComputeSurfaceData(hitRecord);
        }
    }
} // namespace Engine   
} // namespace DynRay

#endif //DYNRAY_SCENE_HPP