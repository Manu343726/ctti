#include "type_id.hpp"
#include <iostream>

int main()
{
    static_assert(ctti::type_id<struct A>() != ctti::type_id<struct B>(), "???");
    std::cout << ctti::type_id<struct FIND_ME_IN_THE_DISASSEMBLY>().name().c_str() << "\n";
}
