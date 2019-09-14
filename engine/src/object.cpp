#include "object.hpp"
#include "glm/gtx/intersect.hpp"
#include "glm/gtc/constants.hpp"
#include "material.hpp"
#include "scene.hpp"
namespace DynRay
{
namespace Engine
{
	Object::Object() = default;
	Object::~Object() = default;
	Object::Object(Object&&) = default;
	Object& Object::operator=(Object&&) = default;

	glm::vec4 Sphere::GetColorAt(const glm::vec4& point, const Scene& scene) const
	{
		return m_Material.Shade(this, point, scene);
	}

    glm::vec4 Sphere::GetNormal(const glm::vec4& point) const
    {
        return (point - m_Center) * (1.f / m_Radius);
    }
    
    void Sphere::GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) const
    {
        outNormal = GetNormal(point);
        
        outTexCoords.x = (1.f + glm::atan(outNormal.z, outNormal.x) * glm::one_over_pi<float>()) * 0.5f;
        outTexCoords.y = glm::acos(outNormal.y) * glm::one_over_pi<float>();
    }

    float Sphere::Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const
    {
        float distance = -1.f;
        bool result = glm::intersectRaySphere(rayOrigin, rayDirection, m_Center, m_Radius * m_Radius, distance);
        if (!result)
            distance = -1.f;

        return distance;
    }

	Plane::Plane(const glm::vec4& normal, const glm::vec4& pos)
		: m_Pos(pos)
		, m_Normal(normal)
	{
		glm::vec3 n = normal;
		glm::vec3 k = glm::vec3(0.f, 1.f, 0.f);
		if (glm::dot(k, n) > 0.8f)
		{ 
			k = glm::vec3(0.f, 0.f, 1.f); 
		}

		glm::vec3 u = glm::cross(k, n);
		glm::vec3 v = glm::cross(n, u);
		m_u.x = u.x; m_u.y = u.y; m_u.z = u.z; m_u.w = 0.f;
		m_v.x = v.x; m_v.y = v.y; m_v.z = v.z; m_v.w = 0.f;
	}

	void Plane::GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) const
	{
		outNormal = m_Normal;
		constexpr float scale = 1.f;

		auto dotx = glm::dot(m_u, point);
		auto doty = glm::dot(m_v, point);

		outTexCoords.x = glm::abs(fmodf(dotx * scale, 1.f));
		outTexCoords.y = glm::abs(fmodf(doty * scale, 1.f));
		if (dotx < 0) outTexCoords.x = 1.f - outTexCoords.x;
		if (doty < 0) outTexCoords.y = 1.f - outTexCoords.y;
	}

	float Plane::Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const
	{
		float denom = glm::dot(m_Normal, rayDirection);
		if (glm::abs(denom) > glm::epsilon<float>()) 
		{
			glm::vec4 p0l0 = m_Pos - rayOrigin;
			return glm::dot(p0l0, m_Normal) / denom;
		}

		return -1.f;
	}

}
}