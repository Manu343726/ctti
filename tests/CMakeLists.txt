add_subdirectory(static)

add_executable(ctti-test
    main.cpp
    cstring.cpp
    hash.cpp
    nameof.cpp
    name_filters.cpp
    detailed_nameof.cpp
    tie.cpp
    map.cpp
    model.cpp
    symbol.cpp
)

if(NOT MSVC)
    target_compile_options(ctti-test PRIVATE -std=c++11 -DCATCH_CONFIG_NO_POSIX_SIGNALS)
endif()

add_test(ctti-test ctti-test)
