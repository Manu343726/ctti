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
#endif

#define CTTI_PRETTY_FUNCTION_BEGIN (sizeof(CTTI_PRETTY_FUNCTION_PREFIX) - 1)
#define CTTI_PRETTY_FUNCTION_END (sizeof(CTTI_PRETTY_FUNCTION) - 1 - sizeof(CTTI_PRETTY_FUNCTION_SUFFIX) - 1)
#define CTTI_PRETTY_FUNCTION_LENGTH (CTTI_PRETTY_FUNCTION_END - CTTI_PRETTY_FUNCTION_BEGIN)

#endif //CTTI_PRETTY_FUNCTION_HPP
