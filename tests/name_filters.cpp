#include <ctti/detail/name_filters.hpp>
#include "catch.hpp"

using namespace ctti::detail;

TEST_CASE("name_filters")
{
    constexpr cstring foo_full{"foo::foo::foo::foo"};
    constexpr cstring foobar{"foo::bar"};

    SECTION("find_ith")
    {
        REQUIRE(find_ith(foo_full, "foo", 0) == foo_full.begin());
        REQUIRE(find_ith(foo_full, "foo", 1) == foo_full.begin() + cstring("foo::").length());
        REQUIRE(find_ith(foo_full, "foo", 2) == foo_full.begin() + cstring("foo::foo::").length());

        REQUIRE(find_ith(foo_full, "::", 0) == foo_full.begin() + cstring{"foo"}.length());
        REQUIRE(find_ith(foo_full, "::", 1) == foo_full.begin() + cstring("foo::foo").length());
        REQUIRE(find_ith(foo_full, "::", 2) == foo_full.begin() + cstring("foo::foo::foo").length());

        REQUIRE(find_ith(foobar, "foo", 1) == foobar.end());
        REQUIRE(find_ith(foobar, "foo", 2) == foobar.end());
        REQUIRE(find_ith(foobar, "foo", 3) == foobar.end());

        REQUIRE(find_ith(foobar, "::", 1) == foobar.end());
    }

    SECTION("find")
    {
        REQUIRE(find(foo_full, "foo") == foo_full.begin());
        REQUIRE(find(foo_full, "::") == foo_full.begin() + cstring{"foo"}.length());
    }

    SECTION("find_last")
    {
        REQUIRE(find_last(foo_full, "foo") == foo_full.begin() + cstring("foo::foo::foo::").length());
        REQUIRE(find_last(foo_full, "::") == foo_full.begin() + cstring("foo::foo::foo").length());
    }
}
