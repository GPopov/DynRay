#include "light.hpp"
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



}
}
