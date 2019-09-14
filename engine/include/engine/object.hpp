#ifndef DYNRAY_OBJECT_HPP
#define DYNRAY_OBJECT_HPP
#include "glm/glm.hpp"
#include <memory>
#include <string>
#include "material.hpp"

namespace DynRay
{
namespace Engine
{
	struct Scene;
    struct Object
    {
		Object();
		~Object();
		Object(Object&&);
		Object& operator=(Object&&);
        
		DiffuseMaterial m_Material{glm::vec3(1.f, 0.f, 0.f)};
	};

    struct Sphere : public Object
    {
        glm::vec4 GetNormal(const glm::vec4& point) const;
        void GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) const;
		glm::vec4 GetColorAt(const glm::vec4& point, const Scene& scene) const;
        float Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const;
        
        glm::vec4 m_Center;
        float m_Radius;
    };

	struct Plane : public Object
	{
		Plane(const glm::vec4& normal, const glm::vec4& pos);
		void GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) const;

		float Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const;

		glm::vec4 m_u;
		glm::vec4 m_v;
		glm::vec4 m_Normal;
		glm::vec4 m_Pos;
	};

} // namespace Engine
} // namespace DynRay
#endif //DYNRAY_OBJECT_HPP