#include <ctti/tie.hpp>
#include "catch.hpp"

CTTI_DEFINE_SYMBOL(a);
CTTI_DEFINE_SYMBOL(b);
CTTI_DEFINE_SYMBOL(c);

struct Struct
{
    int a;
    std::string b;
    bool c;
};

TEST_CASE("tie")
{
    int var_a;
    std::string var_b;
    bool var_c;
    Struct object{42, "foo", true};

    ctti::tie<a, b, c>(var_a, var_b, var_c) = object;

    REQUIRE(var_a == 42);
    REQUIRE(var_b == "foo");
    REQUIRE(var_c == true);
}
