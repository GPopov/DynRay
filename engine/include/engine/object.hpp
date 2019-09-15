#ifndef DYNRAY_OBJECT_HPP
#define DYNRAY_OBJECT_HPP
#include "glm/glm.hpp"
#include <memory>
#include <string>
#include "material.hpp"
#include "glm/gtx/intersect.hpp"

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
		virtual void GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) const = 0;
		inline glm::vec4 GetColorAt(const glm::vec4 &point, const Scene &scene) const;
		DiffuseMaterial m_Material{glm::vec3(1.f, 0.f, 0.f)};
	};

	inline glm::vec4 Object::GetColorAt(const glm::vec4 &point, const Scene &scene) const
	{
		return m_Material.Shade(this, point, scene);
	}

    struct Sphere : public Object
    {
        glm::vec4 GetNormal(const glm::vec4& point) const;
        void GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) const override;
		
        inline float Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const;
        
        glm::vec4 m_Center;
        float m_Radius;
    };

	inline float Sphere::Intersect(const glm::vec4 &rayOrigin, const glm::vec4 &rayDirection) const
	{
		float distance = -1.f;
		bool result = glm::intersectRaySphere(rayOrigin, rayDirection, m_Center, m_Radius * m_Radius, distance);
		if (!result)
			distance = -1.f;

		return distance;
	}

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