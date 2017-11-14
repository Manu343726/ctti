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
        std::vector<int> a{1, 2, 3, 4};
        std::unordered_map<Enum, std::string> b{ {Enum::A, "A"}, {Enum::B, "B"} };

        using ctti_model = ctti::model<symbols::a, symbols::b>;
    };

    Bar d;

    using ctti_model = ctti::model<symbols::a, symbols::b, symbols::c, symbols::d>;
};

ctti::model<symbols::A, symbols::B> ctti_model(ctti::type_tag<Foo::Enum>);

TEST_CASE("serialization")
{
    Foo foo{42, "42", Foo::Enum::A};
    std::ostringstream ss;

    ctti::serialization::serialize(ctti::serialization::json_formatter(), ctti::serialization::ostream_otuput(ss), foo);
    REQUIRE(ss.str() == R"({"a": 42, "b": "42", "c": A, "d": {"a": [1, 2, 3, 4], "b": [{B: "B"}, {A: "A"}]}})");
}
