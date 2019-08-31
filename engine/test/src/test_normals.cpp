#include <catch2/catch.hpp>
#include "engine/camera.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/epsilon.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"

TEST_CASE("Sphere object normals", "[normals]")
{
    DynRay::Engine::Object* sphere1 = nullptr;
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
    glm::vec4 normal; glm::vec2 uv;
    sphere1->GetSurfaceDataAt(glm::vec4(-1.f, 0.f, 0.f, 1.f), normal, uv);

    glm::vec4 expectedNormal = glm::vec4(-1.f, 0.f, 0.f, 0.f);

    CHECK(normal.x == Approx(expectedNormal.x));
    CHECK(normal.y == Approx(expectedNormal.y));
    CHECK(normal.z == Approx(expectedNormal.z));
    CHECK(normal.w == Approx(expectedNormal.w));
}