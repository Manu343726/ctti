#include "ctti/type_id.hpp"
#include <iostream>

int main()
{
    static_assert(ctti::detail::make_array("hello").size() != ctti::detail::make_array("?").size(), "???");

	std::cout << ctti::type_id(std::cout).name() << "!!!\n";
	std::cin.get();
}
