#ifndef DYNRAY_OBJECT_HPP
#define DYNRAY_OBJECT_HPP
#include "glm/glm.hpp"
#include <memory>
#include <vector>
#include <string>
#include <array>
#include "material.hpp"
#include "hitrecord.hpp"
#include "glm/gtx/intersect.hpp"
#include "glm/gtc/constants.hpp"

namespace DynRay
{
namespace Engine
{
	struct Scene;

	template <typename T>
	class Intersectable
	{
	public:
		inline void Intersect(glm::vec4 rayOrigin, glm::vec4 rayDirection, HitRecord& hitRecord) const
		{
			const T* underlying = static_cast<const T*>(this);
			underlying->IntersectImpl(rayOrigin, rayDirection, hitRecord);
		}
	private:
		Intersectable() = default;
		friend T;
	};
	
	struct AABB
	{
		bool Intersect(glm::vec4 rayOrigin, glm::vec4 rayDirection) const;
		glm::vec3 m_Position;
		glm::vec3 m_HalfExtents;
	};

    struct Object
    {
		Object();
		~Object();
		Object(Object&&);
		Object& operator=(Object&&);
        virtual void ComputeSurfaceData(HitRecord& hitRecord) const = 0;
		inline glm::vec4 GetColorAt(const HitRecord& hitRecord, const Scene &scene) const;
		DiffuseMaterial m_Material{glm::vec3(1.f, 0.f, 0.f)};
	};

	inline glm::vec4 Object::GetColorAt(const HitRecord& hitRecord, const Scene &scene) const
	{
		return m_Material.Shade(hitRecord, scene);
	}

	//---------------------------------------------------------
	//--------------------TRIANGLE MESH------------------------
	//---------------------------------------------------------
	struct TriangleMesh : public Object, public Intersectable<TriangleMesh>
	{
		void ComputeSurfaceData(HitRecord& hitRecord) const override;
		inline void IntersectImpl(glm::vec4 rayOrigin, glm::vec4 rayDirection, HitRecord& hitRecord) const;
		void RecomputeAABB();

		std::vector<glm::vec3> m_Vertices;
		std::vector<glm::vec3> m_VertexNormals;
		std::vector<glm::vec2> m_TextureCoordinates;
		std::vector<size_t> m_TriangleIndices;
		AABB m_BoundingVolume;
	};

	void TriangleMesh::IntersectImpl(glm::vec4 rayOrigin, glm::vec4 rayDirection, HitRecord& hitRecord) const
	{
		assert(m_TriangleIndices.size() % 3 == 0);
		const glm::vec3 o(rayOrigin);
		const glm::vec3 d(rayDirection);
		float distance = -1.f;
		glm::vec2 baryPos;

#ifndef DYNRAY_SKIP_BROADPHASE_OPTIMIZATIONS
		//Early out if there's no collision with the AABB of the mesh
		if (!m_BoundingVolume.Intersect(rayOrigin, rayDirection))
			return;
#endif //!defined(DYNRAY_SKIP_BROADPHASE_OPTIMIZATIONS)

		//TODO: Early out if hitRecord.t can't possibly be improved by colliding with this mesh
		for (uint32_t i = 0; i < m_TriangleIndices.size(); i += 3)
		{
			const glm::vec3& v0 = m_Vertices[m_TriangleIndices[i+0]];
			const glm::vec3& v1 = m_Vertices[m_TriangleIndices[i+1]];
			const glm::vec3& v2 = m_Vertices[m_TriangleIndices[i+2]];
			const bool result = glm::intersectRayTriangle(o, d, v0, v1, v2, baryPos, distance);
			if (result && 
				distance < hitRecord.t &&
				distance > hitRecord.minDistance)
			{
				hitRecord.t = distance;
				hitRecord.hitObject = this;
				hitRecord.triangleIndex = i / 3;
				hitRecord.hitBary = baryPos;
			}
		}
	}
	//---------------------------------------------------------
	//-------------------------SPHERE--------------------------
	//---------------------------------------------------------
    struct Sphere : public Object, public Intersectable<Sphere>
    {
        glm::vec4 GetNormal(glm::vec4 point) const;
        void ComputeSurfaceData(HitRecord& hitRecord) const override;
		
        inline void IntersectImpl(glm::vec4 rayOrigin, glm::vec4 rayDirection, HitRecord& hitRecord) const;
        
        glm::vec4 m_Center;
        float m_Radius;
    };

	inline void Sphere::IntersectImpl(glm::vec4 rayOrigin, glm::vec4 rayDirection, HitRecord& hitRecord) const
	{
		float distance = -1.f;
		bool result = glm::intersectRaySphere(rayOrigin, rayDirection, m_Center, m_Radius * m_Radius, distance);
		if (result && 
			distance < hitRecord.t &&
			distance > hitRecord.minDistance)
		{
			hitRecord.t = distance;
			hitRecord.hitObject = this;
		}
	}

	//---------------------------------------------------------
	//--------------------------PLANE--------------------------
	//---------------------------------------------------------
	struct Plane : public Object, public Intersectable<Plane>
	{
		Plane(const glm::vec4& normal, const glm::vec4& pos);
		void ComputeSurfaceData(HitRecord& hitRecord) const override;

		inline void IntersectImpl(glm::vec4 rayOrigin, glm::vec4 rayDirection, HitRecord& hitRecord) const;

		glm::vec4 m_u;
		glm::vec4 m_v;
		glm::vec4 m_Normal;
		glm::vec4 m_Pos;
	};

    inline void Plane::IntersectImpl(glm::vec4 rayOrigin, glm::vec4 rayDirection, HitRecord& hitRecord) const
    {

        float denom = glm::dot(m_Normal, rayDirection);
        if (glm::abs(denom) > glm::epsilon<float>())
        {
            glm::vec4 p0l0 = m_Pos - rayOrigin;
            float distance = glm::dot(p0l0, m_Normal) / denom;
            if (distance < hitRecord.t &&
                distance > hitRecord.minDistance)
            {
                hitRecord.t = distance;
                hitRecord.hitObject = this;
            }
        }
    }

} // namespace Engine
} // namespace DynRay
#endif //DYNRAY_OBJECT_HPP