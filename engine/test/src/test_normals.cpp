#include <catch2/catch.hpp>
#include <memory>
#include "engine/camera.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/epsilon.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"
#include "engine/hitrecord.hpp"

TEST_CASE("Sphere object normals", "[normals]")
{
   auto sphere = std::make_unique<DynRay::Engine::Sphere>();
   glm::vec4 s1_c = glm::vec4(0.f, 0.f, 0.f, 1.f);
   sphere->m_Center = s1_c;
   sphere->m_Radius = 1.f;

   DynRay::Engine::HitRecord hitRecord;
   hitRecord.hitObject = sphere.get();
   hitRecord.hitPos = glm::vec4(-1.f, 0.f, 0.f, 1.f);
   sphere->ComputeSurfaceData(hitRecord);

   glm::vec4 expectedNormal = glm::vec4(-1.f, 0.f, 0.f, 0.f);

   CHECK(hitRecord.hitNormal.x == Approx(expectedNormal.x));
   CHECK(hitRecord.hitNormal.y == Approx(expectedNormal.y));
   CHECK(hitRecord.hitNormal.z == Approx(expectedNormal.z));
   CHECK(hitRecord.hitNormal.w == Approx(expectedNormal.w));
   CHECK(glm::length(hitRecord.hitNormal) == Approx(1.f));
}

TEST_CASE("Plane object normals", "[normals]")
{
   
   auto plane = std::make_unique<DynRay::Engine::Plane>(glm::normalize(glm::vec4(0.f, 0.f, 1.f, 0.f)), glm::vec4(0.f, 0.f, 0.f, 1.f));

   DynRay::Engine::HitRecord hitRecord;
   hitRecord.hitObject = plane.get();
   hitRecord.hitPos = glm::vec4(-1.f, 3.f, 0.f, 1.f);

   plane->ComputeSurfaceData(hitRecord);

   glm::vec4 expectedNormal = glm::vec4(0.f, 0.f, 1.f, 0.f);

   CHECK(hitRecord.hitNormal.x == Approx(expectedNormal.x));
   CHECK(hitRecord.hitNormal.y == Approx(expectedNormal.y));
   CHECK(hitRecord.hitNormal.z == Approx(expectedNormal.z));
   CHECK(hitRecord.hitNormal.w == Approx(expectedNormal.w));
   CHECK(glm::length(hitRecord.hitNormal) == Approx(1.f));
}