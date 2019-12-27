#pragma once
#include "glm/glm.hpp"
namespace DynRay
{
namespace Engine
{
	struct Object;

	struct HitRecord
	{
        static constexpr uint32_t INVALID_TRIANGLE_INDEX = 0xFFFFFFFF;
		glm::vec4 hitPos;
		glm::vec4 hitNormal;
		union
		{
			glm::vec2 hitUV;
			glm::vec2 hitBary;
		};
		
		const Object* hitObject = nullptr;
		uint32_t triangleIndex = INVALID_TRIANGLE_INDEX;
		
		float t = std::numeric_limits<float>::infinity();
		float minDistance = 0.f;
	};
}
}