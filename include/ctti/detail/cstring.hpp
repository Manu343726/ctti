#ifndef CTTI_DETAIL_CSTRING_HPP
#define CTTI_DETAIL_CSTRING_HPP

#include "hash.hpp"
#include <ostream>
#include <string>

namespace ctti
{

namespace detail
{

class cstring
{
public:
    constexpr cstring(const char* begin, std::size_t length) :
        _str{begin},
        _length{length}
    {}

    explicit constexpr cstring(const char* str) :
        cstring{str, length(str)}
    {}

    constexpr cstring(const char* begin, const char* end) :
        cstring{begin, static_cast<std::size_t>(end - begin)}
    {}

    static constexpr std::size_t length(const char* str)
    {
        return *str ? 1 + length(str + 1) : 0;
    }

    constexpr std::size_t length() const
    {
        return _length;
    }

    constexpr hash_t hash() const
    {
        return sid_hash(length(), begin());
    }

    std::string cppstring() const
    {
        return {begin(), length()};
    }

    constexpr const char* begin() const
    {
        return _str;
    }

    constexpr const char* end() const
    {
        return _str + _length;
    }

    constexpr char operator[](std::size_t i) const
    {
        return _str[i];
    }

    constexpr const char* operator()(std::size_t i) const
    {
        return _str + i;
    }

    constexpr cstring operator()(std::size_t begin, std::size_t end) const
    {
        return {_str + begin, _str + end};
    }

    friend std::ostream& operator<<(std::ostream& os, const cstring& str)
    {
        for(const char c : str)
        {
            os << c;
        }

        return os;
    }

private:
    const char* _str;
    std::size_t _length;
};

}

}

#endif // CTTI_DETAIL_CSTRING_HPP
