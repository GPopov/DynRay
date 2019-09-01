#include "light.hpp"
#include "glm/gtc/constants.hpp"
namespace DynRay
{
namespace Engine
{

	OmniLight::OmniLight(const glm::vec4& pos, const glm::vec3& color, float intensity)
		: m_Position(pos)
		, m_Color(color)
		, m_Intensity(intensity)
	{
		
	}

	void OmniLight::GetShadingInfoAt(const glm::vec4& pos, float& outDistance, glm::vec4& outDirection, glm::vec3& outIntensity) const
	{
		glm::vec4 toPos = pos - m_Position;
		outDistance = glm::length(toPos);
		outDirection = toPos / outDistance;
		float attenuation = 4.f * glm::pi<float>() * outDistance;
		outIntensity = m_Color * m_Intensity / attenuation;
	}

}
}
