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