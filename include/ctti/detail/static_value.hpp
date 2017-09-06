#ifndef CTTI_DETAIL_STATIC_VALUE_HPP
#define CTTI_DETAIL_STATIC_VALUE_HPP

namespace ctti
{

namespace detail
{

template<typename T, T Value>
struct static_value
{
    using value_type = T;
    static constexpr value_type value = Value;
};

}

}

#define CTTI_STATIC_VALUE(x) ::ctti::detail::static_value<decltype(x), (x)>

#endif // CTTI_DETAIL_STATIC_VALUE_HPP
