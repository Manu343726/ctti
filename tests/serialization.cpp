#include <ctti/serialization.hpp>
#include <sstream>
#include "catch.hpp"

namespace symbols
{
    CTTI_DEFINE_SYMBOL(A);
    CTTI_DEFINE_SYMBOL(B);
    CTTI_DEFINE_SYMBOL(a);
    CTTI_DEFINE_SYMBOL(b);
    CTTI_DEFINE_SYMBOL(c);
    CTTI_DEFINE_SYMBOL(d);
}

struct Foo
{
    enum class Enum
    {
        A, B
    };

    int a;
    std::string b;
    Enum c;

    struct Bar
    {
        struct enum_hash
        {
            std::size_t operator()(Foo::Enum value) const
            {
                return std::hash<ctti::meta::type_t<std::underlying_type<Foo::Enum>>>()(
                    static_cast<ctti::meta::type_t<std::underlying_type<Foo::Enum>>>(value)
                );
            }
        };

        std::vector<int> a{1, 2, 3, 4};
        std::unordered_map<Enum, std::string, enum_hash> b{ {Enum::A, "A"}, {Enum::B, "B"} };

        using ctti_model = ctti::model<symbols::a, symbols::b>;
    };

    Bar d;

    using ctti_model = ctti::model<symbols::a, symbols::b, symbols::c, symbols::d>;
    void ctti_ostream_print();
};

ctti::model<symbols::A, symbols::B> ctti_model(ctti::type_tag<Foo::Enum>);
void ctti_ostream_print(ctti::type_tag<Foo::Enum>);

TEST_CASE("serialization")
{
    Foo foo{42, "42", Foo::Enum::A};
    std::ostringstream ss;

    SECTION("json formatter")
    {
        ctti::serialization::serialize(ctti::serialization::json_formatter(), ctti::serialization::ostream_otuput(ss), foo);
        REQUIRE(ss.str() == R"({"a": 42, "b": "42", "c": A, "d": {"a": [1, 2, 3, 4], "b": [{B: "B"}, {A: "A"}]}})");
        ss.str("");
    }

    SECTION("default ostream print")
    {
        std::ostringstream ss;
        ss << foo;
        REQUIRE(ss.str() == R"({"a": 42, "b": "42", "c": A, "d": {"a": [1, 2, 3, 4], "b": [{B: "B"}, {A: "A"}]}})");
        ss.str("");

        ss << Foo::Enum::A;
        REQUIRE(ss.str() == "A");
    }
}
