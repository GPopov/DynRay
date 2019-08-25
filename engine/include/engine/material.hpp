#ifndef DYNRAY_MATERIAL_HPP
#define DYNRAY_MATERIAL_HPP
#include "glm/glm.hpp"
namespace DynRay
{
namespace Engine
{
	struct Material
	{
		Material();
		virtual ~Material();
		Material(const Material&);
		Material(Material&&);
		Material& operator=(const Material&);
		Material& operator=(Material&&);
	};

	struct DiffuseMaterial : public Material
	{

	};
}
}
#endif