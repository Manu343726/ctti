# CTTI [![badge](https://img.shields.io/badge/conan.io-ctti%2F0.0.1-green.svg?logo=data:image/png;base64%2CiVBORw0KGgoAAAANSUhEUgAAAA4AAAAOCAMAAAAolt3jAAAA1VBMVEUAAABhlctjlstkl8tlmMtlmMxlmcxmmcxnmsxpnMxpnM1qnc1sn85voM91oM11oc1xotB2oc56pNF6pNJ2ptJ8ptJ8ptN9ptN8p9N5qNJ9p9N9p9R8qtOBqdSAqtOAqtR%2BrNSCrNJ/rdWDrNWCsNWCsNaJs9eLs9iRvNuVvdyVv9yXwd2Zwt6axN6dxt%2Bfx%2BChyeGiyuGjyuCjyuGly%2BGlzOKmzOGozuKoz%2BKqz%2BOq0OOv1OWw1OWw1eWx1eWy1uay1%2Baz1%2Baz1%2Bez2Oe02Oe12ee22ujUGwH3AAAAAXRSTlMAQObYZgAAAAFiS0dEAIgFHUgAAAAJcEhZcwAACxMAAAsTAQCanBgAAAAHdElNRQfgBQkREyOxFIh/AAAAiklEQVQI12NgAAMbOwY4sLZ2NtQ1coVKWNvoc/Eq8XDr2wB5Ig62ekza9vaOqpK2TpoMzOxaFtwqZua2Bm4makIM7OzMAjoaCqYuxooSUqJALjs7o4yVpbowvzSUy87KqSwmxQfnsrPISyFzWeWAXCkpMaBVIC4bmCsOdgiUKwh3JojLgAQ4ZCE0AMm2D29tZwe6AAAAAElFTkSuQmCC)](http://www.conan.io/source/ctti/0.0.1/Manu343726/testing) [![Build Status](https://travis-ci.org/Manu343726/ctti.svg?branch=master)](https://travis-ci.org/Manu343726/ctti) [![Join the chat at https://gitter.im/Manu343726/ctti](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/Manu343726/ctti?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

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

This was tested on Visual Studio 2015, GCC 5.2.0, MinGW GCC 5.1, Clang >3.6.2, and cygwin Clang 3.5.2.
ctti does no use of generalized `constexpr` and must work on C++11 mode, but it needs support of `constexpr` `__func__`-like variables in the compiler.
All major compilers except GCC before 5.1 support this.

## Features

 - **`ctti::nameof<T>()`**: `constexpr` demangled full qualified type names.
 - **`ctti::nameof<T, T Value>()`**: `constexpr` demangled value strings.
 - **`ctti::static_calue<T, Value>`**: `std::integral_constant` on steroids, to pass values as template parameters.
 - **`CTTI_STATIC_VALUE(Value)`**: Handy macro to instance a `ctti::static_value` from the given value.
 - **`ctti::detailed_nameof<>()`**: Alternatives to nameof with detailed name info, supporting non-qualified names, getting qualifiers, etc. See `ctti::name_t` for details. 
 - **`ctti::nameof_v<>` and `ctti::detailed_nameof_v<>`**: C++14 variable template alternatives to the nameof family of functions. Thanks C++ Bruja for this suggestion.
 - **`ctti::type_id<T>()`**: `constexpr` `std::type_info`-like type identifier. See `ctti::type_id_t` bellow for details.
 - **`ctti::id_from_name(name)`**: Get the type id corresponding to the given typename.
 - **`ctti::unnamed_type_id<T>()`**: `constexpr` `std::type_info`-like hash-only type identifier. See `ctti::unnamed_type_id_t` bellow for details.
 - **Symbol based introspection**: Automatic serialization (wip), object conversion, etc. See symbolic introspection bellow.

### Name customization

The names ctti return for a given static value or typename can be overrided with the `ctti_nameof()` function. This can be achieved in two ways:

 - **Intrusive override**: The user defined class defines a `ctti_nameof()` function as part of its static public API:
    ``` cpp
    struct Foo
    {
        static constexpr const char* ctti_nameof()
        {
            return "foo";
        }
    };
    ```
 - **Non-intrusive override**: A `ctti_nameof(type/value tag)` customization point is defined in the type/value namespace:
   ``` cpp
   #include <string>

   namespace std
   {
       constexpr const char* ctti_nameof(ctti::type_tag<std::string>)
       {
            return "std::string"; // instead of "std::__foobar::basic_string<char>"
       }
   }
   ```

### `ctti::detail::cstring`

`cstring` is a `constexpr` implementation of an string view and the core of ctti. All strings returned by the ctti API are represented by this type.
It supports slicing via `operator()(begin index, end index)`, subscript, hashing, string padding, comparison operators, print to `std::ostream`, etc.

``` cpp
constexpr ctti::detail::cstring str{"hello world"};
constexpr ctti::detail::cstring str2{"   hello world   "};

static_assert(str(0, 5) == "hello");
static_assert(str2.pad(2, 2) == str);

constexpr std::uint64_t hash = str.hash(); // fnv1a hash or "hello world"
```

### `ctti::name_t`

`name_t` contains methods to extract information of a name. Given a full qualified name (like those returned by `ctti::nameof()`) a `name_t` can be constructed and
queried:

``` cpp
struct Foo
{
    int i;
};

constexpr ctti::name_t FooName = ctti::detailed_nameof<CTTI_STATIC_VALUE(&Foo::i)>();

int main()
{
    std::cout << FooName.name();                  // prints "i"
    std::cout << FooName.full_name();             // prints "&Foo::i"
    std::cout << FooName.full_homogeneous_name(); // prints "Foo::i"
    std::cout << FooName.qualifier(0);            // prints "Foo"
}
```

All methods in `name_t` are `constexpr` and return `cstring`s.

### `ctti::type_id_t`

A `constexpr` class representing an object identifier. It has the minimal `constexpr` comparable interface to be used as a key type. The id is based on
a fnv1a hash of the type name, which can be obtained by calling `type_id_t::hash()`. `std::hash` is specialized for this type.

``` cpp
std::unordered_map<ctti::type_id_t, void*(*)()> factories;

factories[ctti::type_id<int>()] =         []() -> void* { return new int{}; };
factories[ctti::type_id<std::string>()] = []() -> void* { return new std::string{}; };

void* int_var = factories[ctti::id_from_name("int")]();
```

### `ctti::unnamed_type_id_t`

A lightweight version of `type_id_t` which only stores the type hash (`ctti::type_id_t` stores the name string, which takes one pointer and a `size_t`, and
computes hash on demand. `unnamed_type_id_t` stores the `std::uint64_t` hash only).

``` cpp
struct object
{
    ctti::unnamed_type_id_t type_id;
    void* data;
};
```

### Symbolic introspection

ctti implements object introspection by working with abstract "symbols" defined by the user:

``` cpp
#include <ctti/symbol.hpp>

CTTI_DEFINE_SYMBOL(foo);
```

the `CTTI_DEFINE_SYMBOL` macro defines an abstract identifier, a symbol, in the current namespace. After its definition,
classes can be asked for members through that symbo:

``` cpp
CTTI_DEFINE_SYMBOL(i);

struct my_struct
{
    int i;
};

static_assert(i::is_member_of<my_struct>(), "Has my_struct a member named 'i'?");
```

with symbols as non-intrusive generic member identifiers, objects can be manipulated in a generic way:

``` cpp
#include <ctti/symbol.hpp>
#include <ctti/tie.hpp>

CTTI_DEFINE_SYMBOL(a);
CTTI_DEFINE_SYMBOL(b);
CTTI_DEFINE_SYMBOL(c);

struct foo
{
    int a, b, c;
};


int var_a, var_b;
foo my_foo{1, 2, 3};

ctti::tie<a, b>(var_a, var_b) = my_foo;

assert(var_a == 1);
assert(var_a == 2);
```

``` cpp
struct bar
{
    int a, b;
};

bar my_bar;

// Copy my_foo.a to my_bar.a and my_foo.b to my_bar.b:
ctti::map(my_foo, my_bar, ctti::mapping<a, a>(), ctti::mapping<b, b>());
```

### Conditional features

ctti has a set of conditional features that depend on non-C++11 language features. This ctti features can be controlled by different macros:

 - `ctti::nameof_v/detailed_nameof_v` are declared only if `CTTI_HAS_VARIABLE_TEMPLATES` is defined. Enabled by default if the compiler supports variable templates.
 - `ctti::nameof/detailed_nameof` could work with enum values if the compiler prints those values as part of their `PRETTY_FUNCTION` variables. ctti controls this
 by defining the `CTTI_HAS_ENUM_AWARE_PRETTY_FUNCTION`. If this macro is not defined ctti gives no guarantee you will get the right string from an enum value.

## Acknowledgments

Thanks a lot to Jonathan "foonathan" Müller, both for the `constexpr` hash and the idea for the `__PRETTY_FUNCTION__` trick.

## License

This project is licensed under the MIT license. See LICENSE.md for more details.
