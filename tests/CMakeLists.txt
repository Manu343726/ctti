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
    serialization.cpp
)

target_link_libraries(ctti-test PRIVATE ctti)

if(NOT MSVC)
    target_compile_options(ctti-test PRIVATE -ftemplate-backtrace-limit=0 -DCATCH_CONFIG_NO_POSIX_SIGNALS)
endif()

add_test(ctti-test ctti-test)
