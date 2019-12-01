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
     m_u.x = u.x; m_u.y = u.y; m_u.z = u.z; m_u.w = 0.f;
     m_v.x = v.x; m_v.y = v.y; m_v.z = v.z; m_v.w = 0.f;
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