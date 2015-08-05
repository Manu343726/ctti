//
// Created by manu343726 on 4/08/15.
//

#include "type_id.hpp"
#include <iostream>

int main()
{
    static_assert(ctti::type_id<int>() == ctti::type_id(1), "???");
    static_assert(ctti::type_id<int>() != ctti::type_id<int*>(), "???");

    std::cout << ctti::type_id<int>().name() << std::endl;
}
