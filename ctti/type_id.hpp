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

		// note: name().c_str() isn't null-terminated properly!
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

    using type_index = type_id_t; // To mimic std::type_index when using maps

    namespace detail
    {
        template<typename T>
        constexpr ctti::type_id_t type_id()
        {
			// one-liner required by MSVC :(
			return detail::make_string(CTTI_PRETTY_FUNCTION).
					template trim<CTTI_PRETTY_FUNCTION_LEFT, CTTI_PRETTY_FUNCTION_RIGHT>();
        }
    }

    /**
     * Returns type information at compile-time for a value
     * of type T. Decay is applied to argument type first, use
     * ctti::type_id<decltype(arg)>() to conserve references and cv qualifiers.
     */
    template<typename T>
    constexpr type_id_t type_id(T&&)
    {
        return detail::type_id<typename std::decay<T>::type>();
    }

    /**
     * Returns type information at compile-time for type T.
     */
    template<typename T>
    constexpr type_id_t type_id()
    {
        return detail::type_id<T>();
    }

    static_assert(type_id<void>() == type_id<void>(), "ctti::type_id_t instances must be constant expressions");
}

namespace std
{
    template<>
    struct hash<ctti::type_id_t>
    {
        constexpr std::size_t operator()(const ctti::type_id_t& id) const
        {
			// quiet warning about possible loss of data
            return std::size_t(id.hash());
        }
    };
}

#endif //CTTI_HASH_HPP
