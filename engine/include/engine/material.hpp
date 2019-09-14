#ifndef DYNRAY_MATERIAL_HPP
#define DYNRAY_MATERIAL_HPP
#include "glm/glm.hpp"
namespace DynRay
{
namespace Engine
{
	struct Scene;
	struct Object;
	struct Material
	{
		Material();
		~Material();
		Material(const Material&);
		Material(Material&&);
		Material& operator=(const Material&);
		Material& operator=(Material&&);
	};

	struct DiffuseMaterial : public Material
	{
		DiffuseMaterial(const glm::vec3& albedo);
		
		template<typename ObjectType>
		glm::vec4 Shade(const ObjectType* object, const glm::vec4& p, const Scene& scene) const;

		glm::vec3 m_Albedo;
	};
}
}
#endif