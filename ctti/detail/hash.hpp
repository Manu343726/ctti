#ifndef CTTI_DETAIL_HASH_HPP
#define CTTI_DETAIL_HASH_HPP

#include <cstdint>

namespace ctti
{
    namespace detail
    {
        // From https://github.com/foonathan/string_id. As usually, thanks Jonathan.

        using hash_t = std::uint64_t;

        constexpr hash_t fnv_basis = 14695981039346656037ull;
        constexpr hash_t fnv_prime = 109951162821ull;

        // FNV-1a 64 bit hash
        constexpr hash_t sid_hash(std::size_t n, const char *str, hash_t hash = fnv_basis)
        {
            return n > 0 ? sid_hash(n - 1, str + 1, (hash ^ *str) * fnv_prime) : hash;
        }
    }
}

#endif /* CTTI_DETAIL_HASH_HPP */