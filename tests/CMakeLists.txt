add_subdirectory(static)

add_executable(ctti-test
    main.cpp
    cstring.cpp
    hash.cpp
    nameof.cpp
)

if(NOT MSVC)
    target_compile_options(ctti-test PRIVATE -std=c++11)
endif()

add_test(ctti-test ctti-test)
