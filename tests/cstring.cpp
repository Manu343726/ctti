#include <ctti/detail/cstring.hpp>
#include "catch.hpp"

using namespace ctti::detail;

TEST_CASE("cstring")
{

    SECTION("initialization")
    {
        SECTION("initialization from string literal")
        {
            constexpr cstring hello{"hello"};
            constexpr cstring hello_world{"hello, world"};
            constexpr const char* hello_buff = hello.begin();

            REQUIRE(hello.str() == "hello");
            REQUIRE(hello.length() == 5);
            REQUIRE(hello.end() == hello.begin() + 5);
        }

        SECTION("initialization from const char*")
        {
            constexpr const char* str = "hello";
            constexpr cstring hello{str};

            REQUIRE(hello.length() == 5);
            REQUIRE(hello.str() == "hello");
            REQUIRE(hello.end() == hello.begin() + 5);
        }

        SECTION("initialization from const char* and length")
        {
            constexpr const char* str = "hello world";
            constexpr cstring hello{str, 5};

            REQUIRE(hello.length() == 5);
            REQUIRE(hello.str() == "hello");
            REQUIRE(hello.end() == hello.begin() + 5);
        }
    }

    SECTION("comparison")
    {
        constexpr cstring hello{"hello"};

        REQUIRE(hello == hello);
        REQUIRE(hello != "world");
    }

    SECTION("slices")
    {
        SECTION("slice")
        {
            constexpr cstring hello_world{"hello world"};
            constexpr auto hello = hello_world(0, 5);
            constexpr auto world = hello_world(6, 11);

            REQUIRE(hello.begin() == hello_world.begin());
            REQUIRE(world.begin() == hello_world.begin() + 6);
            REQUIRE(hello.length() == 5);
            REQUIRE(world.length() == 5);

            REQUIRE(hello == "hello");
            REQUIRE(world == "world");
            REQUIRE(hello.str() == "hello");
            REQUIRE(world.str() == "world");
        }

        SECTION("pad")
        {
            constexpr cstring hello_world{"   hello world   "};
            constexpr auto padded = hello_world.pad(3, 3);

            REQUIRE(padded == "hello world");
            REQUIRE(padded.length() == hello_world.length() - 6);
        }
    }
}
