#include "scene.hpp"
namespace DynRay
{
namespace Engine
{

template <>
void Scene::AddObject<Sphere>(Sphere &&sphere)
{
	m_Spheres.push_back(std::move(sphere));
}

template <>
void Scene::AddObject<Plane>(Plane &&plane)
{
   m_Planes.push_back(std::move(plane));
}

template <>
void Scene::AddObject<TriangleMesh>(TriangleMesh&& mesh)
{
    m_Meshes.push_back(std::move(mesh));
}

}
}