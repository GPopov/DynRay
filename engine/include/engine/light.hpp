#ifndef DYNRAY_LIGHT_HPP
#define DYNRAY_LIGHT_HPP
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
namespace DynRay
{
namespace Engine
{
    
//OmniLight is final, because lights are stored by value in the scene
struct OmniLight final
{
	OmniLight(const glm::vec4& pos, const glm::vec3& color, float intensity);
	inline void GetShadingInfoAt(const glm::vec4& pos, float& outDistance, glm::vec4& outDirection, glm::vec3& outIntensity) const;

protected:
	glm::vec4 m_Position = glm::vec4(0.f, 0.f, 0.f, 1.f);
	glm::vec3 m_Color;
	float m_Intensity = 0.f;
};

//--------------------------------------------------------
//--------------------INLINE FUNCTIONS--------------------
//--------------------------------------------------------

inline void OmniLight::GetShadingInfoAt(const glm::vec4& pos, float& outDistance, glm::vec4& outDirection, glm::vec3& outIntensity) const
{
	glm::vec4 toPos = pos - m_Position;
	outDistance = glm::length(toPos);
	outDirection = toPos / outDistance;
	float attenuation = 4.f * glm::pi<float>() * outDistance;
	outIntensity = m_Color * m_Intensity / attenuation;
}
} // namespace Engine
} // namespace DynRay

#endif //DYNRAY_LIGHT_HPP