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
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(&Struct::member)>().full_name() == "&Struct::member");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(&Namespace::Struct::member)>().full_name() == "&Namespace::Struct::member");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Enum::Value)>().full_name() == "Enum::Value");

#ifdef CTTI_HAS_ENUM_AWARE_PRETTY_FUNCTION
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Namespace::Struct::Enum::Value)>().full_name() == "Namespace::Struct::Enum::Value");
#else
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Namespace::Struct::Enum::Value)>().full_name() == "(Namespace::Struct::Enum)0");
#endif // CTTI_HAS_ENUM_AWARE_PRETTY_FUNCTION
    }

    SECTION("full_homogeneous_name")
    {
        REQUIRE(detailed_nameof<Struct>().full_homogeneous_name() == "Struct");
        REQUIRE(detailed_nameof<Enum>().full_homogeneous_name() == "Enum");
        REQUIRE(detailed_nameof<Namespace::Struct>().full_homogeneous_name() == "Namespace::Struct");
        REQUIRE(detailed_nameof<Namespace::Struct::Enum>().full_homogeneous_name() == "Namespace::Struct::Enum");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(&Struct::member)>().full_homogeneous_name() == "Struct::member");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(&Namespace::Struct::member)>().full_homogeneous_name() == "Namespace::Struct::member");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Enum::Value)>().full_homogeneous_name() == "Enum::Value");

#ifdef CTTI_HAS_ENUM_AWARE_PRETTY_FUNCTION
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Namespace::Struct::Enum::Value)>().full_homogeneous_name() == "Namespace::Struct::Enum::Value");
#else
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Namespace::Struct::Enum::Value)>().full_homogeneous_name() == "(Namespace::Struct::Enum)0");
#endif // CTTI_HAS_ENUM_AWARE_PRETTY_FUNCTION
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
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Enum::Value)>().name() == "Value");

#ifdef CTTI_HAS_ENUM_AWARE_PRETTY_FUNCTION
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Namespace::Struct::Enum::Value)>().name() == "Value");
#else
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Namespace::Struct::Enum::Value)>().name() == "Enum)0");
#endif // CTTI_HAS_ENUM_AWARE_PRETTY_FUNCTION
    }

    SECTION("qualifiers")
    {
        REQUIRE(detailed_nameof<Struct>().qualifier(0) == "");
        REQUIRE(detailed_nameof<Struct>().qualifier(1) == "");
        REQUIRE(detailed_nameof<Struct>().qualifier(2) == "");
        REQUIRE(detailed_nameof<Enum>().qualifier(0) == "");
        REQUIRE(detailed_nameof<Enum>().qualifier(1) == "");
        REQUIRE(detailed_nameof<Enum>().qualifier(2) == "");
        REQUIRE(detailed_nameof<Namespace::Struct>().qualifier(0) == "Namespace");
        REQUIRE(detailed_nameof<Namespace::Struct>().qualifier(1) == "");
        REQUIRE(detailed_nameof<Namespace::Struct>().qualifier(2) == "");
        REQUIRE(detailed_nameof<Namespace::Struct::Enum>().qualifier(0) == "Namespace");
        REQUIRE(detailed_nameof<Namespace::Struct::Enum>().qualifier(1) == "Struct");
        REQUIRE(detailed_nameof<Namespace::Struct::Enum>().qualifier(2) == "");
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Enum::Value)>().qualifier(0) == "Enum");

#ifdef CTTI_HAS_ENUM_AWARE_PRETTY_FUNCTION
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Namespace::Struct::Enum::Value)>().qualifier(0) == "Namespace");
#else
        REQUIRE(detailed_nameof<CTTI_STATIC_VALUE(Namespace::Struct::Enum::Value)>().qualifier(0) == "(Namespace");
#endif // CTTI_HAS_ENUM_AWARE_PRETTY_FUNCTION
    }

#ifdef CTTI_HAS_VARIABLE_TEMPLATES
    SECTION("variable templates")
    {
        REQUIRE(detailed_nameof_v<int> == detailed_nameof<int>());
        REQUIRE(detailed_nameof_value_v<int, 42> == detailed_nameof<int, 42>());
    }
#endif // CTTI_HAS_VARIABLE_TEMPLATES
}
