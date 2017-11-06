#ifndef CTTI_DETAIL_META_HPP
#define CTTI_DETAIL_META_HPP

#include <type_traits>

namespace ctti
{

namespace detail
{

template<typename T>
using void_t = typename std::conditional<sizeof(T) == sizeof(T), void, void>::type;

}

}

#endif // CTTI_DETAIL_META_HPP
