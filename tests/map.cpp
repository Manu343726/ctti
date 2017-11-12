#include <ctti/map.hpp>
#include "catch.hpp"

struct Foo
{
    int i;
    std::string str;
};

struct Bar
{
    int j;
    std::string anotherString;
};

CTTI_DEFINE_SYMBOL(i);
CTTI_DEFINE_SYMBOL(str);
CTTI_DEFINE_SYMBOL(j);
CTTI_DEFINE_SYMBOL(anotherString);

TEST_CASE("map")
{
    Foo foo{42, "foo"};
    Bar bar;

    ctti::map(foo, bar, ctti::mapping<i, j>(), ctti::mapping<str, anotherString>());

    REQUIRE(bar.j == 42);
    REQUIRE(bar.anotherString == "foo");
}
