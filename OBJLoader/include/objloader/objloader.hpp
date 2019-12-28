#ifndef DYNRAY_OBJ_LOADER_HPP
#define DYNRAY_OBJ_LOADER_HPP
#include <vector>
#include <string>
#include "engine/object.hpp"

namespace DynRay
{
namespace OBJLoader
{
	void LoadOBJMeshes(const std::string& inputfile, std::vector<Engine::TriangleMesh>& outMeshes);
} // namespace OBJLoader
} // namespace DynRay
#endif //DYNRAY_OBJECT_HPP