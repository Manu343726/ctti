#include <ctti/detail/hash.hpp>
#include "catch.hpp"

using namespace ctti::detail;

TEST_CASE("fnv1a_hash")
{
    // http://www.isthe.com/chongo/tech/comp/fnv/
    // challenge 56 "strings yielding 64 bit fnv1 zero hash"
    SECTION("64 bit FNV1 zero hash")
    {
        REQUIRE(fnv1a_hash("!0IC=VloaY") == 0);
        REQUIRE(fnv1a_hash("=. hx\"iX<;") == 0);
    }
}
