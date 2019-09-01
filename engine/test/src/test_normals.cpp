#include <catch2/catch.hpp>
#include "engine/camera.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/epsilon.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"

TEST_CASE("Sphere object normals", "[normals]")
{
    auto sphere = std::make_unique<DynRay::Engine::Sphere>();
    glm::vec4 s1_c = glm::vec4(0.f, 0.f, 0.f, 1.f);
    sphere->m_Center = s1_c;
    sphere->m_Radius = 1.f;
    sphere->m_Name = "S1";

    glm::vec4 normal; glm::vec2 uv;
    sphere->GetSurfaceDataAt(glm::vec4(-1.f, 0.f, 0.f, 1.f), normal, uv);

    glm::vec4 expectedNormal = glm::vec4(-1.f, 0.f, 0.f, 0.f);

    CHECK(normal.x == Approx(expectedNormal.x));
    CHECK(normal.y == Approx(expectedNormal.y));
    CHECK(normal.z == Approx(expectedNormal.z));
    CHECK(normal.w == Approx(expectedNormal.w));
    CHECK(glm::length(expectedNormal) == Approx(1.f));
}

TEST_CASE("Plane object normals", "[normals]")
{
    
    auto plane = std::make_unique<DynRay::Engine::Plane>(glm::normalize(glm::vec4(0.f, 0.f, 1.f, 0.f)), glm::vec4(0.f, 0.f, 0.f, 1.f));
    plane->m_Name = "P1";

    glm::vec4 normal; glm::vec2 uv;
    plane->GetSurfaceDataAt(glm::vec4(-1.f, 3.f, 0.f, 1.f), normal, uv);

    glm::vec4 expectedNormal = glm::vec4(0.f, 0.f, 1.f, 0.f);

    CHECK(normal.x == Approx(expectedNormal.x));
    CHECK(normal.y == Approx(expectedNormal.y));
    CHECK(normal.z == Approx(expectedNormal.z));
    CHECK(normal.w == Approx(expectedNormal.w));
    CHECK(glm::length(normal) == Approx(1.f));
}