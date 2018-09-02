#include <ctti/detail/cstring.hpp>
#include "static_test.hpp"

using namespace ctti::detail;

constexpr cstring hello{"hello"};
constexpr cstring world{"world"};

EXPECT_EQ(hello.length(), 5);
EXPECT_EQ((cstring{"hello", 5}.length()), 5);
EXPECT_EQ(hello.begin() + hello.size(), hello.end());
EXPECT_EQ(hello, hello);
EXPECT_NE(hello, world);
