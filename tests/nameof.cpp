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

class MyClass
{
public:
    class InnerClass {};
};

struct MyStruct
{
    struct InnerStruct {};
};

enum ClassicEnum { A, B, C };
enum class EnumClass { A, B, C };

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
        REQUIRE(nameof<MyClass>() == "MyClass");
        REQUIRE(nameof<MyClass::InnerClass>() == "MyClass::InnerClass");
    }

    SECTION("struct types")
    {

        REQUIRE(nameof<MyStruct>() == "MyStruct");
        REQUIRE(nameof<MyStruct::InnerStruct>() == "MyStruct::InnerStruct");
    }

    SECTION("enum types")
    {
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

#ifdef CTTI_HAS_VARIABLE_TEMPLATES
    SECTION("variable templates")
    {
        REQUIRE(ctti::nameof_v<int> == nameof<int>());
        REQUIRE(ctti::nameof_value_v<int, 42> == nameof<int, 42>());
    }
#endif // CTTI_HAS_VARIABLE_TEMPLATES
}

TEST_CASE("nameof.enums", "[!mayfail]")
{
#ifdef CTTI_HAS_ENUM_AWARE_PRETTY_FUNCTION
    SECTION("enum values")
    {
        REQUIRE(nameof<CTTI_STATIC_VALUE(ClassicEnum::A)>() == "ClassicEnum::A");
        REQUIRE(nameof<CTTI_STATIC_VALUE(EnumClass::A)>() == "EnumClass::A");
        REQUIRE(nameof<CTTI_STATIC_VALUE(ClassicEnum::A)>() == "ClassicEnum::A");
    }
#else
    SECTION("enum values")
    {
        WARN("Thie section may fail in GCC due to 'u' suffix in integer literals. "
            "It seems that some GCC versions use unsigned int as default enum underlying type");

        REQUIRE(nameof<CTTI_STATIC_VALUE(ClassicEnum::A)>() == "(ClassicEnum)0");
        REQUIRE(nameof<CTTI_STATIC_VALUE(EnumClass::A)>() == "(EnumClass)0");
        REQUIRE(nameof<CTTI_STATIC_VALUE(ClassicEnum::A)>() == "(ClassicEnum)0");
    }
#endif
}
