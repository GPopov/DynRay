#include <catch2/catch.hpp>
#include <dynray.hpp>

TEST_CASE("mul is called", "[DynRay]")
{
    REQUIRE(DynRay::Mul(0, 4) == 0);
    REQUIRE(DynRay::Mul(4, 4) == 16);
    REQUIRE(DynRay::Mul(1, 4) == 4);
    REQUIRE(DynRay::Mul(0, 1) == 0);
}