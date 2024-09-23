#include <iostream>
#include <string>

#include "task/task.h"

int main() {
    std::string number;
    std::cin >> number;

    std::cout << eliminate_unset_bits(number) << std::endl;

    return 0;
}