//
// Created by manu343726 on 4/08/15.
//

#include "type_id.hpp"
#include <iostream>

int main()
{
    constexpr ctti::detail::array<char,6> hello = "hello";
    constexpr ctti::detail::array<char,6> world{'w','o','r','l','d'};
    constexpr ctti::detail::string str = "hello world!!!";
    constexpr ctti::detail::string str2 = str.substr<6,11>();
    constexpr auto arr = ctti::detail::make_array("hello world!!!");
    constexpr auto world_arr = arr.subarray<6,11>();

    std::cout << hello.data() << "\n";
    std::cout << str2.c_str() << "\n";
    std::cout << ctti::type_id<struct foo>().name().c_str() << "\n";
}
