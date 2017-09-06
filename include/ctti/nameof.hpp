#ifndef CTTI_NAMEOF_HPP
#define CTTI_NAMEOF_HPP

#include <ctti/detail/pretty_function.hpp>
#include <ctti/detail/static_value.hpp>

namespace ctti
{

template<typename T>
constexpr ctti::detail::cstring nameof();

template<typename T, T Value>
constexpr ctti::detail::cstring nameof()
{
    return ctti::pretty_function::value<T, Value>().pad(
        CTTI_VALUE_PRETTY_FUNCTION_LEFT + nameof<T>().size() + CTTI_VALUE_PRETTY_FUNCTION_SEPARATION,
        CTTI_VALUE_PRETTY_FUNCTION_RIGHT
    );
}

namespace detail
{

template<typename T>
struct nameof_impl
{
    static constexpr ctti::detail::cstring apply()
    {
        return ctti::pretty_function::type<T>().pad(
            CTTI_TYPE_PRETTY_FUNCTION_LEFT,
            CTTI_TYPE_PRETTY_FUNCTION_RIGHT
        );
    }
};

template<typename T, T Value>
struct nameof_impl<ctti::detail::static_value<T, Value>>
{
    static constexpr ctti::detail::cstring apply()
    {
        return ctti::nameof<T, Value>();
    }
};

}

template<typename T>
constexpr ctti::detail::cstring nameof()
{
    return ctti::detail::nameof_impl<T>::apply();
}

}

#endif // CTTI_NAMEOF_HPP
