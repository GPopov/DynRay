#include "scene.hpp"
namespace DynRay
{
namespace Engine
{
	float Scene::Trace(const glm::vec4& rayOrigin, const glm::vec4& rayDirection, Object*& hitObject, float sqrMin, float sqrMax) const
	{
		float minSqrDistance = sqrMax;
		float minDistance = std::numeric_limits<float>::infinity();
		hitObject = nullptr;
		for (const auto& object : m_Objects)
		{
			glm::vec4 intersectionPoint;
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

}
}