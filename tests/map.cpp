#include <ctti/map.hpp>
#include <sstream>
#include "catch.hpp"

struct Foo
{
    int i;
    std::string str;
};

struct Bar
{
    int j;
    std::string anotherString;
};

CTTI_DEFINE_SYMBOL(i);
CTTI_DEFINE_SYMBOL(str);
CTTI_DEFINE_SYMBOL(j);
CTTI_DEFINE_SYMBOL(anotherString);

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

TEST_CASE("map")
{
    Foo foo{42, "foo"};
    Bar bar;

    ctti::map(foo, bar, ctti::mapping<i, j>(), ctti::mapping<str, anotherString>());

    REQUIRE(bar.j == 42);
    REQUIRE(bar.anotherString == "foo");

    foo.str = "42";
    foo.i = 0;

    ctti::map(foo, bar, ctti::mapping<i, anotherString>(value_to_string()), ctti::mapping<str, j>(string_to_value()));
    REQUIRE(bar.anotherString == "0");
    REQUIRE(bar.j == 42);
}
