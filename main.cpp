#include "src/vec3.h"

#include <iostream>
int main() {
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    Vec3 vec = Vec3();
    std::cout << vec << "\n";
    for (int i = 1; i <= 5; i++) {
        std::cout << "i = " << i << std::endl;
    }

    return 0;
}