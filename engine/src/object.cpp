#include "object.hpp"
#include "glm/gtx/intersect.hpp"
#include "glm/gtc/constants.hpp"
#include "material.hpp"
#include "scene.hpp"
namespace DynRay
{
namespace Engine
{
	bool AABB::Intersect(glm::vec4 rayOrigin, glm::vec4 rayDirection) const
	{
        const glm::vec3 max = m_Position + m_HalfExtents;
        const glm::vec3 min = m_Position - m_HalfExtents;
        float tMin = 0;
        float tMax = std::numeric_limits<float>::infinity();
        for (uint32_t i = 0; i < 3; ++i)
        {
            if (glm::abs(rayDirection[i]) < glm::epsilon<float>())
            {
                //Ray is parallel to slab, if the origin is not inside the box we can early out (no way to hit)
                if (((rayOrigin[i] - min[i]) < glm::epsilon<float>()) || 
                    ((max[i] - rayOrigin[i]) < glm::epsilon<float>())) 
                    return false;
            }
            else
            {
                float ood = 1.f / rayDirection[i];
                float t1 = (min[i] - rayOrigin[i]) * ood;
                float t2 = (max[i] - rayOrigin[i]) * ood;
                if (t1 > t2) std::swap(t1, t2); //make t1 be the intersection with the near plane, if it wasn't

                tMin = std::max(tMin, t1);
                tMax = std::min(tMax, t2);

                if (tMin > tMax)
                    return false;
            }
        }
        return true;
	}

   Object::Object() = default;
   Object::~Object() = default;
   Object::Object(Object&&) = default;
   Object& Object::operator=(Object&&) = default;

   void TriangleMesh::ComputeSurfaceData(HitRecord& hitRecord) const
   {
	   const glm::vec2& bary = hitRecord.hitBary;
	  
	   auto baryInterpolate = [](const glm::vec2& bary, const auto& v0, const auto& v1, const auto& v2)
	   {
		   return (1.f - bary.x - bary.y) * v0 +
			   bary.x * v1 +
			   bary.y * v2;
	   };

	   assert((hitRecord.triangleIndex * 3) + 2 < m_VertexNormals.size());
	   const glm::vec3& n0 = m_VertexNormals[hitRecord.triangleIndex * 3];
	   const glm::vec3& n1 = m_VertexNormals[hitRecord.triangleIndex * 3 + 1];
	   const glm::vec3& n2 = m_VertexNormals[hitRecord.triangleIndex * 3 + 2];
	   hitRecord.hitNormal = { baryInterpolate(bary, n0, n1, n2), 0.f };

	   assert((hitRecord.triangleIndex * 3) + 2 < m_TextureCoordinates.size());
	   const glm::vec2& st0 = m_TextureCoordinates[hitRecord.triangleIndex * 3];
	   const glm::vec2& st1 = m_TextureCoordinates[hitRecord.triangleIndex * 3 + 1];
	   const glm::vec2& st2 = m_TextureCoordinates[hitRecord.triangleIndex * 3 + 2];
	   hitRecord.hitUV = baryInterpolate(bary, st0, st1, st2);
   }

   void TriangleMesh::RecomputeAABB()
   {
       glm::vec3 max(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
       glm::vec3 min(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());

       for (const auto& v : m_Vertices)
       {
           max = glm::max(v, max);
           min = glm::min(v, min);
       }
       m_BoundingVolume.m_Position = (min + max) * 0.5f;
       m_BoundingVolume.m_HalfExtents = max - m_BoundingVolume.m_Position;
   }

   glm::vec4 Sphere::GetNormal(glm::vec4 point) const
   {
     return (point - m_Center) * (1.f / m_Radius);
   }
   
   void Sphere::ComputeSurfaceData(HitRecord& hitRecord) const
   {
     hitRecord.hitNormal = GetNormal(hitRecord.hitPos);
	 glm::vec2& outTexCoords = hitRecord.hitUV;
     outTexCoords.x = (1.f + glm::atan(hitRecord.hitNormal.z, hitRecord.hitNormal.x) * glm::one_over_pi<float>()) * 0.5f;
     outTexCoords.y = glm::acos(hitRecord.hitNormal.y) * glm::one_over_pi<float>();
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
	 m_u = { u, 0.f };
	 m_v = { v, 0.f };
   }

   void Plane::ComputeSurfaceData(HitRecord& hitRecord) const
   {
	 hitRecord.hitNormal = m_Normal;
	 glm::vec2& outTexCoords = hitRecord.hitUV;


     constexpr float scale = 1.f;
     auto dotx = glm::dot(m_u, hitRecord.hitPos);
     auto doty = glm::dot(m_v, hitRecord.hitPos);

     outTexCoords.x = glm::abs(fmodf(dotx * scale, 1.f));
     outTexCoords.y = glm::abs(fmodf(doty * scale, 1.f));
     if (dotx < 0) outTexCoords.x = 1.f - outTexCoords.x;
     if (doty < 0) outTexCoords.y = 1.f - outTexCoords.y;
   }

   }
}