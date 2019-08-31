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
        std::vector<std::unique_ptr<Object>> m_Objects;
        std::vector<OmniLight> m_Omnis;
		float Trace(const glm::vec4& rayOrigin, const glm::vec4& rayDirection, Object*& hitObject, float sqrMin, float sqrMax = std::numeric_limits<float>::infinity()) const;
		
    };
} // namespace Engine   
} // namespace DynRay

#endif //DYNRAY_SCENE_HPP