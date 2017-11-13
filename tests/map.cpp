#include <ctti/map.hpp>
#include <sstream>
#include "catch.hpp"

struct Foo
{
    int i;
    std::string str;
    int get_i() const
    {
        return i;
    }
};

struct Bar
{
    int j;
    std::string anotherString;

    void set_anotherString(const std::string& str)
    {
        anotherString = str;
    }
};

CTTI_DEFINE_SYMBOL(i);
CTTI_DEFINE_SYMBOL(get_i);
CTTI_DEFINE_SYMBOL(str);
CTTI_DEFINE_SYMBOL(j);
CTTI_DEFINE_SYMBOL(anotherString);
CTTI_DEFINE_SYMBOL(set_anotherString);

template<typename T>
std::string lexical_cast(const T& value)
{
    std::ostringstream ss;
    ss << value;
    return ss.str();
}

template<typename T>
T lexical_cast(const std::string& str)
{
    std::istringstream ss{str};
    T value;
    ss >> value;
    return value;
}

struct string_to_value
{
    template<typename Source, typename SourceSymbol, typename Sink, typename SinkSymbol>
    void operator()(const Source& source, SourceSymbol, Sink& sink, SinkSymbol) const
    {
        ctti::get_member_value<SinkSymbol>(sink) = lexical_cast<typename SinkSymbol::template value_type<Sink>>(ctti::get_member_value<SourceSymbol>(source));
    }
};

struct value_to_string
{
    template<typename Source, typename SourceSymbol, typename Sink, typename SinkSymbol>
    void operator()(const Source& source, SourceSymbol, Sink& sink, SinkSymbol) const
    {
        ctti::get_member_value<SinkSymbol>(sink) = lexical_cast(ctti::get_member_value<SourceSymbol>(source));
    }
};

struct lexical_cast_t
{
    template<typename T>
    std::string operator()(const T& value, ctti::type_tag<std::string>) const
    {
        return lexical_cast(value);
    }

    template<typename T>
    T operator()(const std::string& value, ctti::type_tag<T>) const
    {
        return lexical_cast<T>(value);
    }
};

TEST_CASE("map")
{
    Foo foo{42, "foo"};
    Bar bar;

    SECTION("member to member mapping")
    {
        ctti::map(foo, bar, ctti::mapping<i, j>(), ctti::mapping<str, anotherString>());

        REQUIRE(bar.j == 42);
        REQUIRE(bar.anotherString == "foo");
    }

    SECTION("custom member to member specific mapping")
    {
        foo.str = "42";
        foo.i = 0;
        bar.anotherString = "";
        bar.j = -1;

        ctti::map(foo, bar, ctti::mapping<i, anotherString>(value_to_string()), ctti::mapping<str, j>(string_to_value()));
        REQUIRE(bar.anotherString == "0");
        REQUIRE(bar.j == 42);
    }

    SECTION("generic member-agnostic user defined mapping")
    {
        Foo foo{0, "42"};
        Bar bar{-1, ""};

        ctti::map(foo, bar, ctti::mapping<i, anotherString>(lexical_cast_t()), ctti::mapping<str, j>(lexical_cast_t()));
        REQUIRE(bar.anotherString == "0");
        REQUIRE(bar.j == 42);

        foo.i = 42;

        ctti::map(foo, bar, ctti::mapping<i, set_anotherString>(lexical_cast_t()));
        REQUIRE(bar.anotherString == "42");
    }
}
