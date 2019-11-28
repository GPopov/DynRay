#include <catch2/catch.hpp>
#include "engine/camera.hpp"
#include "engine/renderoptions.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/epsilon.hpp"

TEST_CASE("Raster Space to World Space", "[camera]")
{
    DynRay::Engine::Camera camera;
    camera.m_VerticalFOV = 1.0472f;
	constexpr DynRay::Engine::RenderOptions renderOptions(640, 480);
    SECTION("Camera at origin projects center of screen to 0,0")
    {
        glm::vec3 point(319.5f, 239.5f, -1.f);
        camera.SetCameraMatrix(glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1.f), glm::vec3(0, 1, 0)));
        glm::vec4 worldSpacePoint = camera.RasterToWorldSpace(point, renderOptions);

        CHECK(worldSpacePoint.x == Approx(0.f));
        CHECK(worldSpacePoint.y == Approx(0.f));
        CHECK(worldSpacePoint.z == Approx(-1.f));
        CHECK(worldSpacePoint.w == Approx(1.f));
    }

    SECTION("Camera translated at an offset projects center of screen to the offset")
    {
        glm::vec3 point(319.5f, 239.5f, -1.f);
        camera.SetCameraMatrix(glm::lookAt(glm::vec3(20.f, -15.f, 2.f), glm::vec3(20.f, -15.f, -1.f), glm::vec3(0, 1, 0)));
        glm::vec4 worldSpacePoint = camera.RasterToWorldSpace(point, renderOptions);

        CHECK(worldSpacePoint.x == Approx(20.f));
        CHECK(worldSpacePoint.y == Approx(-15.f));
        CHECK(worldSpacePoint.z == Approx(1.f));
        CHECK(worldSpacePoint.w == Approx(1.f));
    }

    SECTION("Camera rotated to point at positive z axis projects points along positive z")
    {
        glm::vec3 point(319.5f, 239.5f, -1.f);
        camera.SetCameraMatrix(glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1.f), glm::vec3(0, 1, 0)));
        glm::vec4 worldSpacePoint = camera.RasterToWorldSpace(point, renderOptions);

        CHECK(worldSpacePoint.x == Approx(0.f));
        CHECK(worldSpacePoint.y == Approx(0.f));
        CHECK(worldSpacePoint.z == Approx(1.f));
        CHECK(worldSpacePoint.w == Approx(1.f));
    }
}

TEST_CASE("Generate Primary ray direction" "[camera]")
{
    DynRay::Engine::Camera camera;
    camera.m_VerticalFOV = 0.785398f;
	constexpr DynRay::Engine::RenderOptions renderOptions(640, 480);
    SECTION("Camera at origin, oriented along -z axis, top left pixel ray")
    {
        glm::vec4 rayDir = camera.GeneratePrimaryRayDirection(renderOptions, 0, 0);

        glm::vec4 expectedDir = glm::normalize(glm::vec4(-renderOptions.Aspect(), 1.f, -1.f, 0.f));
        CHECK(rayDir.x == Approx(expectedDir.x).epsilon(0.01f));
        CHECK(rayDir.y == Approx(expectedDir.y).epsilon(0.01f));
        CHECK(rayDir.z == Approx(expectedDir.z).epsilon(0.01f));
    }

    SECTION("Camera at origin, oriented along -z axis, bottom right pixel ray")
    {
        glm::vec4 rayDir = camera.GeneratePrimaryRayDirection(renderOptions, renderOptions.m_XResolution-1, renderOptions.m_YResolution - 1);

        glm::vec4 expectedDir = glm::normalize(glm::vec4(renderOptions.Aspect(), -1.f, -1.f, 0.f));
        CHECK(rayDir.x == Approx(expectedDir.x).epsilon(0.01f));
        CHECK(rayDir.y == Approx(expectedDir.y).epsilon(0.01f));
        CHECK(rayDir.z == Approx(expectedDir.z).epsilon(0.01f));
    }

    SECTION("Camera translated, oriented along -z axis, has same directions as non-translated")
    {
        std::random_device rd; 
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-10000, 10000);
        glm::vec3 cameraPos = glm::vec3(dis(gen), dis(gen), dis(gen));
        glm::vec3 cameraLookAt = cameraPos + glm::vec3(0.f, 0.f, -1.f);
        camera.SetCameraMatrix(glm::lookAt(cameraPos, cameraLookAt, glm::vec3(0, 1, 0)));

        glm::vec4 rayDir = camera.GeneratePrimaryRayDirection(renderOptions, 0, 0);

        glm::vec4 expectedDir = glm::normalize(glm::vec4(renderOptions.Aspect(), 1.f, -1.f, 0.f));
        CHECK(rayDir.x == Approx(expectedDir.x).epsilon(0.01f));
        CHECK(rayDir.y == Approx(expectedDir.y).epsilon(0.01f));
        CHECK(rayDir.z == Approx(expectedDir.z).epsilon(0.01f));
    }

    SECTION("Camera rotated, has same directions as the directions of the axis aligned camera, transformed by the ToWorld matrix")
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1000, 1000);
        glm::vec3 cameraPos = glm::vec3(dis(gen), dis(gen), dis(gen));
        glm::vec3 cameraLookAt = glm::vec3(dis(gen), dis(gen), dis(gen));
        camera.SetCameraMatrix(glm::lookAt(cameraPos, cameraLookAt, glm::vec3(0, 1, 0)));

        glm::vec4 rayDir = camera.GeneratePrimaryRayDirection(renderOptions, 0, 0);
        glm::vec4 expectedDir = glm::normalize(camera.m_ViewMatrix * glm::vec4(-renderOptions.Aspect(), 1.f, -1.f, 0.f));
        CHECK(rayDir.x == Approx(expectedDir.x).epsilon(0.05f));
        CHECK(rayDir.y == Approx(expectedDir.y).epsilon(0.05f));
        CHECK(rayDir.z == Approx(expectedDir.z).epsilon(0.05f));
    }
}