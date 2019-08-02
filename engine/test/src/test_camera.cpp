#include <catch2/catch.hpp>
#include "camera.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

TEST_CASE("Raster Space to World", "[camera]")
{
    DynRay::Engine::Camera camera;
    camera.m_VerticalFOV = 1.0472f;
    glm::vec3 point(319.5f, 239.5f, -1.f);

    SECTION("Camera at origin projects center of screen to 0,0")
    {
        glm::vec3 worldSpacePoint = camera.RasterToWorld(point, 640, 480);

        CHECK(worldSpacePoint.x == Approx(0.f));
        CHECK(worldSpacePoint.y == Approx(0.f));
        CHECK(worldSpacePoint.z == Approx(-1.f));
    }

    SECTION("Camera translated at an offset projects center of screen to the offset")
    {
        camera.m_ToWorld[3] = glm::vec4(20.f, -15.f, -2.f, 1.f);

        glm::vec3 worldSpacePoint = camera.RasterToWorld(point, 640, 480);

        CHECK(worldSpacePoint.x == Approx(20.f));
        CHECK(worldSpacePoint.y == Approx(-15.f));
        CHECK(worldSpacePoint.z == Approx(-3.f));
    }

    SECTION("Camera rotation")
    {
        camera.m_ToWorld = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1.f), glm::vec3(0, 1, 0));
        glm::vec3 worldSpacePoint = camera.RasterToWorld(point, 640, 480);

        CHECK(worldSpacePoint.x == Approx(0.f));
        CHECK(worldSpacePoint.y == Approx(0.f));
        CHECK(worldSpacePoint.z == Approx(1.f));
    }
    
}