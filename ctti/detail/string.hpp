//
// Created by manu343726 on 4/08/15.
//

#ifndef CTTI_STRING_HPP
#define CTTI_STRING_HPP

#include <ostream>

#include "hash.hpp"

namespace ctti
{
    namespace detail
    {
        struct string
        {
            template<std::size_t N>
            constexpr string(const char (&str)[N]) :
                str_{str},
                length_{N},
                hash_{sid_hash(length_, str)}
            {}

            constexpr string(const char* str, std::size_t length) :
                str_{str},
                length_{length},
                hash_{sid_hash(length, str)}
            {}

            constexpr hash_t hash() const
            {
                return hash_;
            }

            // note: not necessarily null-terminated!
            constexpr const char* c_str() const
            {
                return str_;
            }

            constexpr std::size_t length() const
            {
                return length_;
            }

            constexpr char operator[](std::size_t i) const
            {
                return str_[i];
            }

            template <std::size_t Left>
            constexpr string trim_left() const
            {
                return string{str_ + Left, length_ - Left};
            }

            template <std::size_t Right>
            constexpr string trim_right() const
            {
                return string{str_, length_ - Right - 1};
            }

            template <std::size_t Left, std::size_t Right>
            constexpr string trim() const
            {
                //.teplate neded by clang 3.6.2, GCC 5.2.0 does not
                return trim_left<Left>().template trim_right<Right>();
            }

            friend std::ostream& operator<<(std::ostream& os, const string& str)
            {
                for (std::size_t i = 0u; i != str.length_; ++i)
                    os << str[i];
                return os;
            }

        private:
            const char* str_;
            std::size_t length_;
            hash_t hash_;
        };

        template<std::size_t N>
        constexpr string make_string(const char (&str)[N])
        {
            return {str};
        }
    }
}

#endif //CTTI_STRING_HPP
