//
// Created by manu343726 on 4/08/15.
//

#ifndef CTTI_STRING_HPP
#define CTTI_STRING_HPP

#include <ostream>

namespace ctti
{
    namespace detail
    {
        struct string
        {
            template<std::size_t N>
            constexpr string(const char (&str)[N]) :
                string{str, N}
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

            template<std::size_t Begin, std::size_t End>
            constexpr string substr() const
            {
                return substr_<Begin>(std::make_index_sequence<End - Begin>{});
            }

            friend std::ostream& operator<<(std::ostream& os, const string& str)
            {
                return os << str.c_str();
            }

        private:
            template<std::size_t Begin, std::size_t... Is>
            constexpr string substr_(std::index_sequence<Is...>) const
            {
                const char str[] = {str_[Begin + Is]...};
                return { str };
            }

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
