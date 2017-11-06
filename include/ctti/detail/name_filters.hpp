#ifndef CTTI_DETAIL_NAMEFILTERS_HPP
#define CTTI_DETAIL_NAMEFILTERS_HPP

#include "cstring.hpp"

namespace ctti
{

namespace detail
{

constexpr ctti::detail::cstring filter_prefix(const ctti::detail::cstring& str, const ctti::detail::cstring& prefix)
{
    return str.size() >= prefix.size() ? (str(0, prefix.size()) == prefix ? str(prefix.size(), str.size()) : str) : str;
}

constexpr ctti::detail::cstring leftpad(const ctti::detail::cstring& str)
{
    return (str.size() > 0 && str[0] == ' ') ? leftpad(str(1, str.size())) : str;
}

constexpr ctti::detail::cstring filter_class(const ctti::detail::cstring& type_name)
{
    return leftpad(filter_prefix(leftpad(type_name), "class"));
}

constexpr ctti::detail::cstring filter_struct(const ctti::detail::cstring& type_name)
{
    return leftpad(filter_prefix(leftpad(type_name), "struct"));
}

constexpr ctti::detail::cstring filter_typename_prefix(const ctti::detail::cstring& type_name)
{
    return filter_struct(filter_class(type_name));
}

}

}

#endif // CTTI_DETAIL_NAMEFILTERS_HPP
