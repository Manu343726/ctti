add_library(ctti-static-tests
    algorithm.cpp
    cstring.cpp
    hash.cpp
    symbol.cpp
    name.cpp
    static_value.cpp
)

if(NOT MSVC)
    target_compile_options(ctti-static-tests PRIVATE -std=c++11)
endif()
