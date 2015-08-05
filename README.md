# CTTI

Compile Time Type Information for the C++ programming language.

## Background

We know C++ is a statically typed compiled language, but it's disappointing that we cannot even get
the name of a C++ type at compile time, having to use RTTI (Run Time Type Information) which introduces
a lot of overhead. In fact, that's one of the most feared features of C++, usually disabled in performance dependent
scenarios such as videogames programming. 

This library aims to provide features similar to RTTI `std::type_info` at compile-time, currently `constexpr` type name and 
a `constexpr` replacement of `std::type_index` for indexing maps with types.

``` cpp
#include "ctti/type_id.hpp"

int main()
{
    static_assert(ctti::type_id<int>() != ctti::type_id("hello"), "compile-time type-id comparison");
    
    std::unordered_map<ctti::type_id_t, std::size_t> sizeof_map;
    
    sizeof_map[ctti::type_id<int>()] = sizeof(int);
}
```

## Support and current status

This was tested on both GCC 5.2.0 and Clang 3.6.2. It's fairly unstable (I'm currently working on it), and it leads 
to ugly ICEs whenever the `constexpr` machinery fails. 

### Current state: Bugs...

`ctti::type_id` comparison and hashing works correctly, but I'm trying to find a bug that 
causes `type_ide::name()` to return empty or even corrupted strings. I'm sure there's something wrong with the
`ctti::detail::string::substr()` function. I'm on it :)

## Acknowledgments 

Thanks a lot to Jonathan "foonathan" Müller, both for the `constexpr` hash and the idea for the `__PRETTY_FUNCTION__` trick.

## License

This project is licensed under the MIT license. See LICENSE.md for more details.