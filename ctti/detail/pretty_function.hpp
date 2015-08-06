//
// Created by manu343726 on 4/08/15.
//

#ifndef CTTI_PRETTY_FUNCTION_HPP
#define CTTI_PRETTY_FUNCTION_HPP

#if defined(__clang__)
    #define CTTI_PRETTY_FUNCTION __PRETTY_FUNCTION__
    #define CTTI_PRETTY_FUNCTION_PREFIX "ctti::type_id_t ctti::detail::type_id() [T = "
    #define CTTI_PRETTY_FUNCTION_SUFFIX "]"
#elif defined(__GNUC__) && !defined(__clang__)
    #define CTTI_PRETTY_FUNCTION __PRETTY_FUNCTION__
    #define CTTI_PRETTY_FUNCTION_PREFIX "ctti::type_id_t ctti::detail::type_id() [T = "
    #define CTTI_PRETTY_FUNCTION_SUFFIX "]"
#elif defined(_MSC_VER)
    #define CTTI_PRETTY_FUNCTION __FUNCSIG__
    #define CTTI_PRETTY_FUNCTION_PREFIX "struct ctti::type_id_t __cdecl ctti::detail::type_id<"
    #define CTTI_PRETTY_FUNCTION_SUFFIX ">(void)"
#else
    #error "No support for this compiler."
#endif

#define CTTI_PRETTY_FUNCTION_LEFT (sizeof(CTTI_PRETTY_FUNCTION_PREFIX) - 1)
#define CTTI_PRETTY_FUNCTION_RIGHT (sizeof(CTTI_PRETTY_FUNCTION_SUFFIX) - 1)
#define CTTI_PRETTY_FUNCTION_BEGIN CTTI_PRETTY_FUNCTION_LEFT
#define CTTI_PRETTY_FUNCTION_END (sizeof(CTTI_PRETTY_FUNCTION) - CTTI_PRETTY_FUNCTION_RIGHT)

#endif //CTTI_PRETTY_FUNCTION_HPP
