#include <catch2/catch.hpp>
#include "engine/light.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/epsilon.hpp"

TEST_CASE("Light Direction", "[light]")
{
	DynRay::Engine::OmniLight light(glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec3(1.f, 1.f, 1.f), 1.f);


	glm::vec4 pos(5.f, 3.2f, 2.7f, 1.f);

	float actualDistance;
	glm::vec4 actualDirection;
	glm::vec3 actualIntensity;
	light.GetShadingInfoAt(pos, actualDistance, actualDirection, actualIntensity);
	

	glm::vec4 expectedDirection = glm::vec4(0.766694f, 0.490684f, 0.414015f, 0.f);
	CHECK(actualDirection.x == Approx(expectedDirection.x));
	CHECK(actualDirection.y == Approx(expectedDirection.y));
	CHECK(actualDirection.z == Approx(expectedDirection.z));
	CHECK(actualDirection.w == Approx(expectedDirection.w));
	CHECK(glm::length(actualDirection) == Approx(1.f));

	CHECK(glm::length(actualDistance) == Approx(6.5215f));


	
	glm::vec3 expectedIntensity = glm::vec3(1.f, 1.f, 1.f) / 81.951585961543346418536515296229f;

	CHECK(actualIntensity.x == Approx(expectedIntensity.x));
	CHECK(actualIntensity.y == Approx(expectedIntensity.y));
	CHECK(actualIntensity.z == Approx(expectedIntensity.z));

}