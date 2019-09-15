#include "scene.hpp"
namespace DynRay
{
namespace Engine
{

namespace
{

}


template <>
void Scene::AddObject<Sphere>(Sphere &&sphere)
{
	//m_Objects.push_back(std::make_unique<Sphere>(std::move(sphere)));
	m_Spheres[m_SphereCount++] = std::move(sphere);
}

template <>
void Scene::AddObject<Plane>(Plane &&plane)
{
	//m_Objects.push_back(std::make_unique<Plane>(std::move(plane)));
	m_Planes.push_back(std::move(plane));
}

}
}