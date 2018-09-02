#include <ctti/type_id.hpp>
#include <iostream>

int main()
{
    std::cout << ctti::type_id<std::ostream>().name() << std::endl;
}
