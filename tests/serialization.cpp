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
        std::array<std::tuple<int, int>, 2> c{{std::make_tuple(1, 2), std::make_tuple(3, 4)}};

        using ctti_model = ctti::model<symbols::a, symbols::b, symbols::c>;
    };

    Bar d;

    using ctti_model = ctti::model<symbols::a, symbols::b, symbols::c, symbols::d>;
    void ctti_ostream_print();
};

ctti::model<symbols::A, symbols::B> ctti_model(ctti::type_tag<Foo::Enum>);
void ctti_ostream_print(ctti::type_tag<Foo::Enum>);

TEST_CASE("serialization")
{
    Foo foo{42, "42", Foo::Enum::A, Foo::Bar{}};
    std::ostringstream ss;

    SECTION("enum to string")
    {
        REQUIRE(ctti::serialization::enum_to_string(Foo::Enum::A) == "A");
        REQUIRE(ctti::serialization::enum_to_string(Foo::Enum::B) == "B");
    }

    SECTION("enum from string")
    {
        REQUIRE(ctti::serialization::enum_from_string<Foo::Enum>("A") == Foo::Enum::A);
        REQUIRE(ctti::serialization::enum_from_string<Foo::Enum>("B") == Foo::Enum::B);
    }

    SECTION("json formatter")
    {
        ctti::serialization::serialize(ctti::serialization::json_formatter(), ctti::serialization::ostream_otuput(ss), foo);
        REQUIRE(ss.str() == R"({"a": 42, "b": "42", "c": A, "d": {"a": [1, 2, 3, 4], "b": [{B: "B"}, {A: "A"}], "c": [(1, 2), (3, 4)]}})");
        ss.str("");
    }

    SECTION("default ostream print")
    {
        std::ostringstream ss;
        ss << foo;
        REQUIRE(ss.str() == R"({"a": 42, "b": "42", "c": A, "d": {"a": [1, 2, 3, 4], "b": [{B: "B"}, {A: "A"}], "c": [(1, 2), (3, 4)]}})");
        ss.str("");

        ss << Foo::Enum::A;
        REQUIRE(ss.str() == "A");
    }

    SECTION("json writer")
    {
        nlohmann::json json;
        ctti::serialization::serialize(ctti::serialization::json_writer(json), foo);
        REQUIRE(json.dump() == R"({"a":42,"b":"42","c":"A","d":{"a":[1,2,3,4],"b":[[1,"B"],[0,"A"]],"c":[[1,2],[3,4]]}})");
    }

    SECTION("json reader enum as int")
    {
        auto json = nlohmann::json::parse(R"({"a":42,"b":"42","c":"A","d":{"a":[1,2,3,4],"b":[[1,"B"],[0,"A"]],"c":[[1,2],[3,4]]}})");
        Foo foo2;
        ctti::serialization::deserialize(ctti::serialization::json_reader(json), foo2);
        REQUIRE(foo2.a == 42);
        REQUIRE(foo2.b == "42");
        REQUIRE(foo2.c == Foo::Enum::A);
        REQUIRE(foo2.d.a == std::vector<int>{1, 2, 3, 4});
        REQUIRE(foo2.d.b.size() == 2);
        REQUIRE(foo2.d.b.at(Foo::Enum::A) == "A");
        REQUIRE(foo2.d.b.at(Foo::Enum::B) == "B");
        REQUIRE(foo2.d.c == std::array<std::tuple<int, int>, 2>{ std::make_tuple(1, 2), std::make_tuple(3, 4)});
    }

    SECTION("json reader enum as string")
    {
        auto json = nlohmann::json::parse(R"({"a":42,"b":"42","c":"A","d":{"a":[1,2,3,4],"b":[["B","B"],["A","A"]],"c":[[1,2],[3,4]]}})");
        Foo foo2;
        ctti::serialization::deserialize(ctti::serialization::json_reader(json), foo2);
        REQUIRE(foo2.a == 42);
        REQUIRE(foo2.b == "42");
        REQUIRE(foo2.c == Foo::Enum::A);
        REQUIRE(foo2.d.a == std::vector<int>{1, 2, 3, 4});
        REQUIRE(foo2.d.b.size() == 2);
        REQUIRE(foo2.d.b.at(Foo::Enum::A) == "A");
        REQUIRE(foo2.d.b.at(Foo::Enum::B) == "B");
        REQUIRE(foo2.d.c == std::array<std::tuple<int, int>, 2>{ std::make_tuple(1, 2), std::make_tuple(3, 4)});
    }
}
