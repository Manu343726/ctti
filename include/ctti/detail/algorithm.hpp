#ifndef CTTI_DETAIL_ALGORITHM_HPP
#define CTTI_DETAIL_ALGORITHM_HPP

#include <cstdint>

namespace ctti
{

namespace detail
{

template<typename T, std::size_t N>
constexpr const T* begin(const T(&array)[N])
{
    return &array[0];
}

template<typename T, std::size_t N>
constexpr const T* end(const T(&array)[N])
{
    return &array[N];
}

template<typename LhsIt, typename RhsIt>
constexpr bool equal_range(LhsIt lhsBegin, LhsIt lhsEnd, RhsIt rhsBegin, RhsIt rhsEnd)
{
    return (lhsBegin != lhsEnd && rhsBegin != rhsEnd) ? *lhsBegin == *rhsBegin &&
        equal_range(lhsBegin + 1, lhsEnd, rhsBegin + 1, rhsEnd) : (lhsBegin == lhsEnd && rhsBegin == rhsEnd);
}

}

}

#endif // CTTI_DETAIL_ALGORITHM_HPP
