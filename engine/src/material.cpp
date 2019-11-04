#include "material.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "hitrecord.hpp"
#include "glm/gtc/constants.hpp"
namespace DynRay
{
namespace Engine
{
   Material::Material() = default;
   Material::~Material() = default;
   Material::Material(const Material&) = default;
   Material::Material(Material&&) = default;
   Material& Material::operator=(const Material&) = default;
   Material& Material::operator=(Material&&) = default;

   DiffuseMaterial::DiffuseMaterial(const glm::vec3& albedo)
     : m_Albedo(albedo)
   {

   }

   glm::vec4 DiffuseMaterial::Shade(const HitRecord& hitRecord, const Scene &scene) const
   {
     constexpr float RAY_BIAS = 0.001f;

     glm::vec4 finalColor = glm::vec4(0.f);
     for (const auto& light : scene.m_Omnis)
     {
       float distance = std::numeric_limits<float>::infinity();
       glm::vec4 L;
       glm::vec3 intensity;
       light.GetShadingInfoAt(hitRecord.hitPos, distance, L, intensity);

       const Object* hitObject = nullptr;
       scene.Trace<Scene::TraceMode::SingleHit>(hitRecord.hitPos, -L, RAY_BIAS, distance);
       float isVisible = hitObject == nullptr;

       float cosTheta = glm::dot(-L, hitRecord.hitNormal);
       finalColor += isVisible * glm::vec4(m_Albedo * glm::one_over_pi<float>() * intensity * glm::max(0.f, cosTheta), 1.f);
     }
     return finalColor;
   }
}
}