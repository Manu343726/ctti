#include <ctti/nameof.hpp>
#include "catch.hpp"

using namespace ctti;

namespace foo
{
    struct Foo {};

    namespace bar
    {
        struct Bar {};
    }

    inline namespace inline_quux
    {
        struct Quux {};
    }
}

namespace bar
{
    struct Bar {};

    constexpr ctti::detail::cstring ctti_nameof(ctti::type_tag<Bar>)
    {
        return "Bar"; // without namespace
    }

    enum class Enum
    {
        A, B, C
    };

    constexpr ctti::detail::cstring ctti_nameof(CTTI_STATIC_VALUE(Enum::C))
    {
        return "Enum::Si";
    }
}

TEST_CASE("nameof")
{
    SECTION("basic types")
    {
        REQUIRE(nameof<int>() == "int");
        REQUIRE(nameof<bool>() == "bool");
        REQUIRE(nameof<char>() == "char");
        REQUIRE(nameof<void>() == "void");
    }

    SECTION("class types")
    {
        class MyClass
        {
        public:
            class InnerClass {};
        };

        REQUIRE(nameof<MyClass>() == "MyClass");
        REQUIRE(nameof<MyClass::InnerClass>() == "MyClass::InnerClass");
    }

    SECTION("struct types")
    {
        struct MyStruct
        {
            struct InnerStruct {};
        };

        REQUIRE(nameof<MyStruct>() == "MyStruct");
        REQUIRE(nameof<MyStruct::InnerStruct>() == "MyStruct::InnerStruct");
    }

    SECTION("enum types")
    {
        enum ClassicEnum {};
        enum class EnumClass {};

        REQUIRE(nameof<ClassicEnum>() == "ClassicEnum");
        REQUIRE(nameof<EnumClass>() == "EnumClass");
    }

    SECTION("with namespaces")
    {
        REQUIRE(nameof<foo::Foo>() == "foo::Foo");
        REQUIRE(nameof<foo::bar::Bar>() == "foo::bar::Bar");

        SECTION("inline namespaces")
        {
            REQUIRE(nameof<foo::inline_quux::Quux>() == "foo::inline_quux::Quux");
            REQUIRE(nameof<foo::Quux>() == "foo::inline_quux::Quux");
        }

        SECTION("std")
        {
            REQUIRE(nameof<std::string>() == "std::string");
        }
    }

    SECTION("with custom ctti_nameof()")
    {
        SECTION("intrusive customize")
        {
            struct Foo
            {
                static constexpr const char* ctti_nameof()
                {
                    return "Foobar";
                }
            };


            REQUIRE(nameof<Foo>() == "Foobar");
        }

        SECTION("non-intrusive customize")
        {
            REQUIRE(nameof<bar::Bar>() == "Bar");
            REQUIRE(nameof<CTTI_STATIC_VALUE(bar::Enum::C)>() == "Enum::Si");
        }
    }
}
