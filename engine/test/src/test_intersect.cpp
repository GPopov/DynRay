#include <catch2/catch.hpp>
#include "engine/object.hpp"

TEST_CASE("AABB/Ray Intersection", "[AABB]")
{
	DynRay::Engine::AABB aabb;
	aabb.m_Position = { 0, 2.5f, 2.5f };
	aabb.m_HalfExtents = { 5.f, 2.5, 2.5 };
	SECTION("Non-colliding: Line never intersects aabb")
	{
		glm::vec4 r0 = { 8,0,3, 1 };
		glm::vec4 r0_dir = glm::normalize(glm::vec4{ 0, 19, 0, 1 } - r0);

		bool intersects = aabb.Intersect(r0, r0_dir);
		CHECK(intersects == false);
	}

	SECTION("Non-colliding: Ray direction away from box")
	{
		glm::vec4 r1 = { 0, -2, 2, 1 };
		glm::vec4 r1_dir = glm::normalize(glm::vec4{ 0, -5, 2, 1 } - r1);


		bool intersects = aabb.Intersect(r1, r1_dir);
		CHECK(intersects == false);
	}

	SECTION("Non-colliding: Ray Origin outside box && ray parallel to one of box faces")
	{
		glm::vec4 r4 = { -6, 0, 3, 1 };
		glm::vec4 r4_dir = glm::normalize(glm::vec4{ -4, 0, 0, 1 } - r4);


		bool intersects = aabb.Intersect(r4, r4_dir);
		CHECK(intersects == false);
	}

	SECTION("Colliding: Ray origin inside box")
	{
		glm::vec4 r2 = { 2, 2, 2, 1 };
		glm::vec4 r2_dir = glm::normalize(glm::vec4{ -2, -2, 0, 1 } - r2);

		DynRay::Engine::HitRecord hitRecord;
		bool intersects = aabb.Intersect(r2, r2_dir);
		CHECK(intersects == true);
	}

	SECTION("Colliding: Ray origin inside box && ray parallel to one of box faces")
	{
		glm::vec4 r5 = { -4, 2, 3, 1 };
		glm::vec4 r5_dir = glm::normalize(glm::vec4{ 0, 2, 3, 1 } - r5);

		bool intersects = aabb.Intersect(r5, r5_dir);
		CHECK(intersects == true);
	}

	SECTION("Colliding: Ray origin outside box")
	{
		glm::vec4 r3 = { 0, 3, 10, 1 };
		glm::vec4 r3_dir = glm::normalize(glm::vec4{ 0, 4, -5, 1 } - r3);

		bool intersects = aabb.Intersect(r3, r3_dir);
		CHECK(intersects == true);
	}
}