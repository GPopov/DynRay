#include <catch2/catch.hpp>
#include "engine/camera.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/epsilon.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"
#include <memory>

TEST_CASE("Trace detects objects correctly along the ray", "[trace]")
{
	DynRay::Engine::Object* sphere1 = nullptr;
	DynRay::Engine::Object* sphere2 = nullptr;
	DynRay::Engine::Scene scene;
	{
		auto sphere = std::make_unique<DynRay::Engine::Sphere>();
		glm::vec4 s1_c = glm::vec4(0.f, 0.f, 0.f, 1.f);
		sphere->m_Center = s1_c;
		sphere->m_Radius = 1.f;
		sphere->m_Name = "S1";
		sphere1 = sphere.get();
		scene.m_Objects.push_back(std::move(sphere));
	}
	{
		auto sphere = std::make_unique<DynRay::Engine::Sphere>();
		glm::vec4 s2_c = glm::vec4(5.f, 0.f, 0.f, 1.f);
		sphere->m_Center = s2_c;
		sphere->m_Radius = 1.f;
		sphere->m_Name = "S2";
		sphere2 = sphere.get();
		scene.m_Objects.push_back(std::move(sphere));
	}

	glm::vec4 rayStart = glm::vec4(3.f, 0.f, 0.f, 1.f);
	glm::vec4 rayDir = glm::vec4(1.f, 0.f, 0.f, 0.f);
	glm::vec4 expectedRayHitPos = glm::vec4(4.f, 0.f, 0.f, 1.f);
	float expectedHitDistance = glm::distance(rayStart, expectedRayHitPos);

	const DynRay::Engine::Object* closestObject = nullptr;
	SECTION("Ray doesn't hit objects behind it or after the max distance")
    {
		float actualHitDistance = scene.Trace(rayStart, rayDir, closestObject, 0.f, expectedHitDistance * expectedHitDistance);
		REQUIRE(closestObject == nullptr);
		REQUIRE(actualHitDistance == Approx( std::numeric_limits<float>::infinity()));
	}

	SECTION("Ray correctly hits objects in front of it")
    {
		float actualHitDistance = scene.Trace(rayStart, rayDir, closestObject, 0.f);
		REQUIRE(closestObject == sphere2);
		REQUIRE(actualHitDistance == Approx( expectedHitDistance ));
	}

	SECTION("Ray does not collides with backfaces (if start is inside an object, object will be discarded)")
    {
		float actualHitDistance = scene.Trace(rayStart, rayDir, closestObject, 0.f);
		{
			auto sphere = std::make_unique<DynRay::Engine::Sphere>();
			glm::vec4 s2_c = glm::vec4(3.f, 0.f, 0.f, 1.f);
			sphere->m_Center = s2_c;
			sphere->m_Radius = 1.f;
			sphere->m_Name = "S3";
			scene.m_Objects.push_back(std::move(sphere));
		}

		REQUIRE(closestObject == sphere2);
		REQUIRE(actualHitDistance == Approx( expectedHitDistance ));
	}


}