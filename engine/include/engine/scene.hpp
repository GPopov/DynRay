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

        float Trace(const glm::vec4& rayOrigin, const glm::vec4& rayDirection, const Object*& hitObject, float sqrMin, float sqrMax = std::numeric_limits<float>::infinity()) const;

        std::vector<std::unique_ptr<Object>> m_Objects;
        std::vector<Sphere> m_Spheres;
        std::vector<Plane> m_Planes;
        std::vector<OmniLight> m_Omnis;	
    };
} // namespace Engine   
} // namespace DynRay

#endif //DYNRAY_SCENE_HPP