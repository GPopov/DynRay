#include <catch2/catch.hpp>

unsigned Factorial(unsigned x)
{

    return x > 1 ? x * Factorial(x-1) : 1;
}

TEST_CASE("Factorials are computed", "[factorial]")
{
    REQUIRE(Factorial(0) == 1);
    REQUIRE(Factorial(1) == 1);
    REQUIRE(Factorial(2) == 2);
    REQUIRE(Factorial(3) == 6);
    REQUIRE(Factorial(10) == 3628800);
}
