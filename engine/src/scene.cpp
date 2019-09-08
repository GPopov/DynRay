#include "scene.hpp"
namespace DynRay
{
namespace Engine
{
template <typename ObjectType>
float Trace_Impl(const std::vector<ObjectType>& objects, const glm::vec4 &rayOrigin, const glm::vec4 &rayDirection, const Object *&hitObject, float sqrMin, float sqrMax)
{
	float minSqrDistance = sqrMax;
	float minDistance = std::numeric_limits<float>::infinity();

	for (const auto &object : objects)
	{
		glm::vec4 intersectionPoint;
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

float Scene::Trace(const glm::vec4 &rayOrigin, const glm::vec4 &rayDirection, const Object *&hitObject, float sqrMin, float sqrMax) const
{
	hitObject = nullptr;
	float sphereHitDistance = Trace_Impl(m_Spheres, rayOrigin, rayDirection, hitObject, sqrMin, sqrMax);
	float planeHitDistance = Trace_Impl(m_Planes, rayOrigin, rayDirection, hitObject, sqrMin, sphereHitDistance * sphereHitDistance);
	return glm::min(sphereHitDistance, planeHitDistance);
}

template <>
void Scene::AddObject<Sphere>(Sphere &&sphere)
{
	//m_Objects.push_back(std::make_unique<Sphere>(std::move(sphere)));
	m_Spheres.push_back(std::move(sphere));
}

template <>
void Scene::AddObject<Plane>(Plane &&plane)
{
	//m_Objects.push_back(std::make_unique<Plane>(std::move(plane)));
	m_Planes.push_back(std::move(plane));
}

}
}