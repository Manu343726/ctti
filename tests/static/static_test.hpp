#ifndef CTTI_TESTS_STATIC_TEST_HPP
#define CTTI_TESTS_STATIC_TEST_HPP

#define PP_STR_IMPL(x) #x
#define PP_STR(...) PP_STR_IMPL((__VA_ARGS__))

#define EXPECT_TRUE(...) \
    static_assert((__VA_ARGS__), "Expected '" PP_STR(__VA_ARGS__) "' to be true")

#define EXPECT_FALSE(...) \
    static_assert(!(__VA_ARGS__), "Expected '" PP_STR(__VA_ARGS__) "' to be false")

#define EXPECT_EQ(x, y) \
    static_assert(x == y, "Expected '" PP_STR(x) "' to be equal to '" PP_STR(y) "'")

#define EXPECT_NE(x, y) \
    static_assert(x != y, "Expected '" PP_STR(x) "' to be not equal to '" PP_STR(y) "'")

#endif // CTTI_TESTS_STATIC_TEST_HPP
