#include <ctti/detail/algorithm.hpp>
#include "static_test.hpp"

using namespace ctti::detail;

constexpr int array_a[] = {1, 2, 3, 4};
constexpr int array_b[] = {1, 2, 3, 42};
constexpr int array_c[] = {1, 2};
constexpr int array_d[] = {1};
constexpr const char* hello_world = "hello world";
constexpr const char* world = "world";

EXPECT_EQ(begin(array_a), &array_a[0]);
EXPECT_EQ(end(array_a), &array_a[sizeof(array_a) / sizeof(int)]);

EXPECT_TRUE(
    ctti::detail::equal_range(
        begin(array_a), end(array_a),
        begin(array_a), end(array_a)
    )
);

EXPECT_FALSE(
    ctti::detail::equal_range(
        begin(array_a), end(array_a),
        begin(array_b), end(array_b)
    )
);

EXPECT_TRUE(
    ctti::detail::equal_range(
        &world[0], &world[5],
        &hello_world[6], &hello_world[11]
    )
);
