//
// Created by manu343726 on 4/08/15.
//

#include "type_id.hpp"
#include <unordered_map>
#include <iostream>

int main()
{
    std::unordered_map<ctti::type_id_t, int> map;
    std::string name = ctti::type_id("hello").name().c_str();

    map[ctti::type_id(1)]   = 1;
    map[ctti::type_id(1u)]  = 2;
    map[ctti::type_id(1ul)] = 3;

    static_assert(ctti::type_id<int>() == ctti::type_id(1), "???");
    static_assert(ctti::type_id<int>() != ctti::type_id<int*>(), "???");

    std::cout << map[ctti::type_id<int>()] << std::endl;
    std::cout << map[ctti::type_id<char>()] << std::endl;
    std::cout << map[ctti::type_id<unsigned long int>()] << std::endl;
    std::cout << ctti::type_id<int>().name() << std::endl;

    std::cin.get();
}
