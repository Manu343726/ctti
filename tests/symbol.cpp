#include <ctti/symbol.hpp>
#include <ctti/nameof.hpp>
#include <ctti/hash_literal.hpp>
#include "catch.hpp"

CTTI_DEFINE_SYMBOL(foo);

#include <ctti/symbol_from_hash.hpp>

TEST_CASE("symbol")
{
    REQUIRE(ctti::nameof<foo>() == ctti::nameof<ctti::symbol_from_hash<"foo"_sh>>());
}
