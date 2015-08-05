//
// Created by manu343726 on 4/08/15.
//

#ifndef CTTI_HASH_HPP
#define CTTI_HASH_HPP

#include <functional>
#include "detail/hash.hpp"
#include "detail/pretty_function.hpp"
#include "detail/string.hpp"

namespace ctti
{
    struct type_id_t
    {
        constexpr type_id_t(const detail::string& name) :
            name_{name}
        {}

        constexpr detail::hash_t hash() const
        {
            return name_.hash();
        }

        constexpr detail::string name() const
        {
            return name_;
        }

        friend constexpr bool operator==(const type_id_t& lhs, const type_id_t& rhs)
        {
            return lhs.hash() == rhs.hash();
        }

        friend constexpr bool operator!=(const type_id_t& lhs, const type_id_t& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        detail::string name_;
    };

    namespace detail
    {
        template<char... Chars>
        struct ct_string
        {
            static constexpr const char value[] = {Chars..., '\0'};
        };

        template<char... Chars>
        constexpr const char ct_string<Chars...>::value[];

        // The trick is to be able to discard both the preffix and suffix of
        // __PRETTY_FUNCTION__ string, getting T name only.
        // This is done in two steps:
        //
        //  - type_id() function bellow gets T name length through CTTI_PRETTY_PRINT_LENGTH macro.
        //  - Then __PRETTY_FUNCTION__ is computed again, using it to fill a variadic char string
        //    template which will hold the T name.
        template<typename T, std::size_t... Is, std::size_t N>
        constexpr const char* parse_name(const char (&pretty_function)[N], std::index_sequence<Is...>)
        {
            constexpr std::size_t fn_length = 4 + sizeof("const char* parse_name(const char (&pretty_function)[N], std::index_sequence<Is...>)");
            using str = ct_string<CTTI_PRETTY_FUNCTION[fn_length + Is]...>;

            return str::value;
        }

        // Since _() is a template, __PRETTY_FUNCTION__ string varies with template parameter,
        // pretty function is usually something like "hash_t _<T>() [with T = *type here*]".
        template<typename T>
        constexpr ctti::type_id_t type_id()
        {
            const auto str = detail::make_string(CTTI_PRETTY_FUNCTION);
            const auto name = str.template substr<CTTI_PRETTY_FUNCTION_BEGIN, CTTI_PRETTY_FUNCTION_END>();

            return {name};
        }
    }

    template<typename T>
    constexpr type_id_t type_id(T&&)
    {
        return detail::type_id<typename std::decay<T>::type>();
    }

    template<typename T>
    constexpr type_id_t type_id()
    {
        return detail::type_id<typename std::decay<T>::type>();
    }

    //static_assert(type_id<void>() == type_id<void>(), "ctti::type_id_t instances must be constant expressions");
}

namespace std
{
    template<>
    struct hash<ctti::type_id_t>
    {
        std::size_t operator()(const ctti::type_id_t& id) const
        {
            return id.hash();
        }
    };
}

#endif //CTTI_HASH_HPP
