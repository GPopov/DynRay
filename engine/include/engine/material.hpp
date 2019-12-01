#ifndef DYNRAY_MATERIAL_HPP
#define DYNRAY_MATERIAL_HPP
#include "glm/glm.hpp"
namespace DynRay
{
namespace Engine
{
   struct Scene;
   struct Object;
   struct HitRecord;
   struct Material
   {
      Material();
      ~Material();
      Material(const Material&);
      Material(Material&&);
      Material& operator=(const Material&);
      Material& operator=(Material&&);
   };

   struct DiffuseMaterial : public Material
   {
      DiffuseMaterial(const glm::vec3& albedo);
      
      glm::vec4 Shade(const HitRecord& hitRecord, const Scene& scene) const;

      glm::vec3 m_Albedo;
   };
}
}
#endif