#include <ctti/name.hpp>
#include "static_test.hpp"

EXPECT_EQ(ctti::name_t{"hello::world"}.name(), "world");
EXPECT_EQ(ctti::name_t{"hello::world"}.full_name(), "hello::world");
EXPECT_EQ(ctti::name_t{"::hello::world"}.name(), "world");
EXPECT_EQ(ctti::name_t{"::hello::world"}.full_name(), "::hello::world");
EXPECT_EQ(ctti::name_t{"world"}.name(), "world");

EXPECT_EQ(ctti::name_t{"hello::world"}.qualifier(0), "hello");
EXPECT_EQ(ctti::name_t{"foo::bar::quux::foobar::foobarquux"}.qualifier(0), "foo");
EXPECT_EQ(ctti::name_t{"foo::bar::quux::foobar::foobarquux"}.qualifier(1), "bar");
EXPECT_EQ(ctti::name_t{"foo::bar::quux::foobar::foobarquux"}.qualifier(2), "quux");
EXPECT_EQ(ctti::name_t{"foo::bar::quux::foobar::foobarquux"}.qualifier(3), "foobar");
EXPECT_EQ(ctti::name_t{"foo::bar::quux::foobar::foobarquux"}.name(), "foobarquux");
EXPECT_EQ(ctti::name_t{"::foo::bar::quux::foobar::foobarquux"}.qualifier(0), "");
EXPECT_EQ(ctti::name_t{"::foo::bar::quux::foobar::foobarquux"}.qualifier(1), "foo");
EXPECT_EQ(ctti::name_t{"::foo::bar::quux::foobar::foobarquux"}.qualifier(2), "bar");
EXPECT_EQ(ctti::name_t{"::foo::bar::quux::foobar::foobarquux"}.qualifier(3), "quux");
EXPECT_EQ(ctti::name_t{"::foo::bar::quux::foobar::foobarquux"}.qualifier(4), "foobar");
EXPECT_EQ(ctti::name_t{"::foo::bar::quux::foobar::foobarquux"}.name(), "foobarquux");
