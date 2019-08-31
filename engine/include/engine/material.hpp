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
		virtual ~Material();
		Material(const Material&);
		Material(Material&&);
		Material& operator=(const Material&);
		Material& operator=(Material&&);
		virtual glm::vec4 Shade(const Object* object, const glm::vec4& p, const Scene& scene) const = 0;
	};

	struct DiffuseMaterial : public Material
	{
		DiffuseMaterial(const glm::vec3& albedo);
		virtual glm::vec4 Shade(const Object* object, const glm::vec4& p, const Scene& scene) const override;
		glm::vec3 m_Albedo;
	};
}
}
#endif