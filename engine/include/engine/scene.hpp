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

		inline float Trace(const glm::vec4& rayOrigin, const glm::vec4& rayDirection, const Object*& hitObject, float sqrMin, float sqrMax = std::numeric_limits<float>::infinity()) const;
		
    };

	inline float Scene::Trace(const glm::vec4& rayOrigin, const glm::vec4& rayDirection, const Object*& hitObject, float sqrMin, float sqrMax) const
	{
		float minSqrDistance = sqrMax;
		float minDistance = std::numeric_limits<float>::infinity();
		hitObject = nullptr;
		for (const auto& object : m_Objects)
		{
			float distance = object->Intersect(rayOrigin, rayDirection);
			float sqrDistance = distance * distance;
			if (distance > 0.f &&
				sqrDistance > sqrMin &&
				sqrDistance < minSqrDistance)
			{
				minSqrDistance = sqrDistance;
				minDistance = distance;
				hitObject = object.get();
			}
		}
		return minDistance;
	}
} // namespace Engine   
} // namespace DynRay

#endif //DYNRAY_SCENE_HPP