#ifndef CTTI_DETAILED_NAMEOF_HPP
#define CTTI_DETAILED_NAMEOF_HPP

#include <ctti/nameof.hpp>
#include <ctti/detail/name_filters.hpp>

namespace ctti
{

struct name_t
{
    constexpr name_t(const ctti::detail::cstring& full_name) :
        _full_name{full_name}
    {}

    constexpr ctti::detail::cstring name() const
    {
        return get_name(left(ctti::detail::find_last(_full_name, "::") + 2));
    }

    constexpr ctti::detail::cstring full_name() const
    {
        return _full_name;
    }

    constexpr ctti::detail::cstring full_homogeneous_name() const
    {
        return ctti::detail::filter_prefix(full_name(), "&");
    }

    constexpr ctti::detail::cstring qualifier(std::size_t i) const
    {
        return right(ctti::detail::find_ith(_full_name, "::", i));
    }

private:
    ctti::detail::cstring _full_name;

    constexpr ctti::detail::cstring left(const char* begin) const
    {
        return {ctti::detail::min(_full_name.end(), begin), _full_name.end()};
    }

    constexpr ctti::detail::cstring get_name(const ctti::detail::cstring& name) const
    {
        return (name != "") ? name : _full_name;
    }

    constexpr ctti::detail::cstring right(const char* end) const
    {
        return end >= _full_name.end() ?
            ctti::detail::cstring{""}
        :
            ctti::detail::cstring{_full_name.begin(), end};
    }
};

template<typename T>
constexpr name_t detailed_nameof()
{
    return {ctti::nameof<T>()};
}

template<typename T, T Value>
constexpr name_t detailed_nameof()
{
    return {ctti::nameof<T, Value>()};
}

}

#endif // CTTI_DETAILED_NAMEOF_HPP
