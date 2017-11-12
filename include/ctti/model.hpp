#ifndef CTTI_MODEL_HPP
#define CTTI_MODEL_HPP

#include <ctti/detail/meta.hpp>
#include <ctti/symbol.hpp>
#include <ctti/type_tag.hpp>

namespace ctti
{

template<typename... Symbols>
struct model
{
    using symbols = ctti::meta::list<Symbols...>;
};

template<typename T>
constexpr ctti::model<> ctti_model(ctti::type_tag<T>);

namespace detail
{
    template<typename T, typename = void>
    struct get_model
    {
        using type = decltype(ctti_model(ctti::type_tag<T>()));
    };

    template<typename T>
    struct get_model<T, ctti::meta::void_t<typename T::ctti_model>>
    {
        using type = typename T::ctti_model;
    };
}

template<typename T>
using get_model = typename ctti::detail::get_model<T>::type;

}

#endif // CTTI_MODEL_HPP
