#pragma once
#include <cstdint>
namespace DynRay
{
namespace Engine
{
struct RenderOptions
{
	inline constexpr RenderOptions(uint32_t width, uint32_t height)
		: m_XResolution(width)
		, m_YResolution(height)
	{

	}
	constexpr float Aspect() const { return float(m_XResolution) / m_YResolution; }
	uint32_t m_XResolution;
	uint32_t m_YResolution;
	
};
};
}