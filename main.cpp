#include "src/monte_carlo.hpp"

#include <chrono>
#include <iostream>
#include <random>


int main() {
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        std::cout << "i = " << i << std::endl;
    }

    monte_carlo_integral(0, 1, 100000);

    return 0;
}

