#include "src/monte_carlo.hpp"
#include "tiny_tracer.hpp"
#include <iostream>


int main() {
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        std::cout << "i = " << i << std::endl;
    }

    monte_carlo_integral_uniform(0, 1, 100000);

    return 0;
}

