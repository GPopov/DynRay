#include "material.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "glm/gtc/constants.hpp"
namespace DynRay
{
namespace Engine
{
	Material::Material() = default;
	Material::~Material() = default;
	Material::Material(const Material&) = default;
	Material::Material(Material&&) = default;
	Material& Material::operator=(const Material&) = default;
	Material& Material::operator=(Material&&) = default;

	DiffuseMaterial::DiffuseMaterial(const glm::vec3& albedo)
		: m_Albedo(albedo)
	{

	}

	glm::vec4 DiffuseMaterial::Shade(const Object* object, const glm::vec4& p, const Scene& scene) const
	{
		constexpr float RAY_BIAS_SQR = 0.001f * 0.001f;
		glm::vec4 hitNormal;
		glm::vec2 texCoords;
		object->GetSurfaceDataAt(p, hitNormal, texCoords);
		glm::vec4 finalColor = glm::vec4(0.f);
		for (const auto& light : scene.m_Omnis)
		{
			glm::vec4 toL = p - light.m_Position;
			glm::vec4 L = glm::normalize(toL);
			float sqrDistance = glm::dot(toL, toL);

			Object* hitObject = nullptr;
			scene.Trace(p, -L, hitObject, RAY_BIAS_SQR, sqrDistance);
			float isVisible = hitObject == nullptr;

			float cosTheta = glm::dot(-L, hitNormal);
			finalColor += isVisible * glm::vec4(m_Albedo * glm::one_over_pi<float>() * light.m_Intensity * light.m_Color * glm::max(0.f, cosTheta), 1.f);
		}
		return finalColor;
	}

}
}