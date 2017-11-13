#ifndef CTTI_SYMBOL_HPP
#define CTTI_SYMBOL_HPP

#include <ctti/detail/meta.hpp>
#include <ctti/detailed_nameof.hpp>
#include <ctti/detail/cstring.hpp>
#include <ctti/detail/preprocessor.hpp>
#include <memory>

#define CTTI_DEFINE_SYMBOL(name)                                             \
    struct name {                                                            \
        constexpr name() {}                                                  \
                                                                             \
        static constexpr ctti::detail::cstring symbol() {                    \
            return CTTI_PP_STR(name);                                        \
        }                                                                    \
                                                                             \
        static constexpr std::uint64_t hash() {                              \
            return symbol().hash();                                          \
        }                                                                    \
                                                                             \
        template<typename T, typename = void>                                \
        struct impl                                                          \
        {                                                                    \
            static constexpr bool is_member_of() {                           \
                return false;                                                \
            }                                                                \
                                                                             \
            using member_type = std::nullptr_t;                              \
                                                                             \
            static constexpr member_type get_member() {                      \
                return nullptr;                                              \
            }                                                                \
        };                                                                   \
                                                                             \
        template<typename T>                                                 \
        struct impl<T, ::ctti::meta::void_t<decltype(T::name)>> {            \
            static constexpr bool is_member_of() {                           \
                return true;                                                 \
            }                                                                \
                                                                             \
            template<typename U, bool IsEnum = std::is_enum<U>::value>       \
            struct traits                                                    \
            {                                                                \
                using member_type = decltype(&U::name);                      \
                                                                             \
                static constexpr member_type get_member() {                  \
                    return &U::name;                                         \
                }                                                            \
            };                                                               \
                                                                             \
            template<typename U>                                             \
            struct traits<U, true>                                           \
            {                                                                \
                using member_type = decltype(U::name);                       \
                                                                             \
                static constexpr member_type get_member() {                  \
                    return U::name;                                          \
                }                                                            \
            };                                                               \
                                                                             \
            using member_type = typename traits<T>::member_type;             \
                                                                             \
            static constexpr member_type get_member() {                      \
                return traits<T>::get_member();                              \
            }                                                                \
        };                                                                   \
                                                                             \
        template<typename T>                                                 \
        using member_type = typename impl<T>::member_type;                   \
                                                                             \
        template<typename T>                                                 \
        static constexpr bool is_member_of() {                               \
            return impl<T>::is_member_of();                                  \
        }                                                                    \
                                                                             \
        template<typename T>                                                 \
        static constexpr member_type<T> get_member() {                       \
            return impl<T>::get_member();                                    \
        }                                                                    \
                                                                             \
        template<typename T>                                                 \
        static constexpr ctti::name_t detailed_name() {                      \
            return ctti::detailed_nameof<CTTI_STATIC_VALUE(get_member<T>())>(); \
        }                                                                    \
                                                                             \
        template<typename T>                                                 \
        using value_type = decltype(T::name);                                \
    };                                                                       \
                                                                             \
    name ctti_symbol_from_hash(::ctti::meta::uint64_t<ctti::detail::fnv1a_hash(CTTI_PP_STR(name))>)


namespace ctti
{

template<typename Symbol, typename T, typename = typename std::enable_if<
    Symbol::template is_member_of<T>()
>::type>
constexpr const typename Symbol::template value_type<T>& get_member_value(const T& object)
{
    return object.*Symbol::template get_member<T>();
}

template<typename Symbol, typename T, typename = typename std::enable_if<
    Symbol::template is_member_of<T>()
>::type>
constexpr typename Symbol::template value_type<T>& get_member_value(T& object)
{
    return object.*Symbol::template get_member<T>();
}

namespace detail
{

template<std::size_t Hash>
struct no_symbol_for_hash
{
};

}

}

template<typename Hash>
ctti::detail::no_symbol_for_hash<Hash::value> ctti_symbol_from_hash(Hash);

#endif // CTTI_SYMBOL_HPP
