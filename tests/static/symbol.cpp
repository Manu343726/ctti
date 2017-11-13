#include <ctti/symbol.hpp>
#include <ctti/hash_literal.hpp>
#include "static_test.hpp"

struct Foo
{
    int foobar;
    int getter() const;
    void setter(int i);
};

enum class Enum
{
    Value
};

CTTI_DEFINE_SYMBOL(foobar);
CTTI_DEFINE_SYMBOL(Value);
CTTI_DEFINE_SYMBOL(getter);
CTTI_DEFINE_SYMBOL(setter);

#include <ctti/symbol_from_hash.hpp>

EXPECT_TRUE(foobar::is_member_of<Foo>());
EXPECT_FALSE(foobar::is_member_of<Enum>());
EXPECT_FALSE(Value::is_member_of<Foo>());
EXPECT_TRUE(Value::is_member_of<Enum>());
EXPECT_TRUE(getter::is_member_of<Foo>());
EXPECT_TRUE(setter::is_member_of<Foo>());

EXPECT_EQ(foobar::get_member<Foo>(), &Foo::foobar);
EXPECT_EQ(foobar::get_member<Enum>(), nullptr);
EXPECT_EQ(Value::get_member<Enum>(), Enum::Value);
EXPECT_EQ(Value::get_member<Foo>(), nullptr);

EXPECT_EQ(foobar::symbol(), "foobar");
EXPECT_EQ(Value::symbol(), "Value");

EXPECT_TRUE(std::is_same<foobar, ctti::symbol_from_hash<"foobar"_sh>>());
