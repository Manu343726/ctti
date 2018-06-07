add_library(ctti-static-tests
    algorithm.cpp
    cstring.cpp
    hash.cpp
    symbol.cpp
    name.cpp
    static_value.cpp
)

target_link_libraries(ctti-static-tests PRIVATE ctti)
