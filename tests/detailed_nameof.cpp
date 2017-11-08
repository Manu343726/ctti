#include <ctti/detailed_nameof.hpp>
#include "catch.hpp"

using namespace ctti;

struct Struct
{
    int member;
};

enum class Enum
{
    Value
};

namespace Namespace
{
    struct Struct
    {
        int member;
        enum class Enum
        {
            Value
        };
    };
};

constexpr ctti::detail::cstring ctti_nameof(CTTI_STATIC_VALUE(Enum::Value))
{
    return "Enum::Value";
}

constexpr ctti::detail::cstring ctti_nameof(CTTI_STATIC_VALUE(Namespace::Struct::Enum::Value))
{
    return "Namespace::Struct::Enum::Value";
}

TEST_CASE("detailed_nameof")
{
    SECTION("full_name")
    {
        REQUIRE(detailed_nameof<Struct>().full_name() == "Struct");
        REQUIRE(detailed_nameof<Enum>().full_name() == "Enum");
        REQUIRE(detailed_nameof<Namespace::Struct>().full_name() == "Namespace::Struct");
        REQUIRE(detailed_nameof<Namespace::Struct::Enum>().full_name() == "Namespace::Struct::Enum");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(&Struct::member)>().full_name() == "&Struct::member");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Enum::Value)>().full_name() == "Enum::Value");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(&Namespace::Struct::member)>().full_name() == "&Namespace::Struct::member");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Namespace::Struct::Enum::Value)>().full_name() == "Namespace::Struct::Enum::Value");
    }

    SECTION("full_homogeneous_name")
    {
        REQUIRE(detailed_nameof<Struct>().full_homogeneous_name() == "Struct");
        REQUIRE(detailed_nameof<Enum>().full_homogeneous_name() == "Enum");
        REQUIRE(detailed_nameof<Namespace::Struct>().full_homogeneous_name() == "Namespace::Struct");
        REQUIRE(detailed_nameof<Namespace::Struct::Enum>().full_homogeneous_name() == "Namespace::Struct::Enum");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(&Struct::member)>().full_homogeneous_name() == "Struct::member");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Enum::Value)>().full_homogeneous_name() == "Enum::Value");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(&Namespace::Struct::member)>().full_homogeneous_name() == "Namespace::Struct::member");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Namespace::Struct::Enum::Value)>().full_homogeneous_name() == "Namespace::Struct::Enum::Value");
    }

    SECTION("name")
    {
        REQUIRE(detailed_nameof<Struct>().name() == "Struct");
        REQUIRE(detailed_nameof<Enum>().name() == "Enum");
        REQUIRE(detailed_nameof<Namespace::Struct>().name() == "Struct");
        REQUIRE(detailed_nameof<Namespace::Struct::Enum>().name() == "Enum");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(&Struct::member)>().name() == "member");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Enum::Value)>().name() == "Value");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(&Namespace::Struct::member)>().name() == "member");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Namespace::Struct::Enum::Value)>().name() == "Value");
    }

    SECTION("qualifiers")
    {
        // TODO: tests
        /*
        REQUIRE(detailed_nameof<Struct>().full_name() == "Struct");
        REQUIRE(detailed_nameof<Enum>().full_name() == "Enum");
        REQUIRE(detailed_nameof<Namespace::Struct>().full_name() == "Namespace::Struct");
        REQUIRE(detailed_nameof<Namespace::Struct::Enum>().full_name() == "&Namespace::Struct::Enum");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(&Struct::member)>().full_name() == "&Struct::member");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Enum::Value)>().full_name() == "Enum::Value");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(&Namespace::Struct::member)>().full_name() == "&namespace::Struct::member");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Namespace::Struct::Enum::Value)>().full_name() == "Namespace::Struct::Enum::Value");
        */
    }
}
