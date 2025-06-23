#include <chrono>
#include <iostream>
#include <random>

void monte_carlo_integral(float a, float b, int num_samples) {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> distribution(a, b);
    // Estimates the integral of f(x) = x between a and b using num_samples number of samples.
    float sum = 0;
    for (int i = 0; i < num_samples; i++) {
        float x = distribution(generator);
        sum += x;
    }

    sum *= (b - a) / static_cast<float>(num_samples);

    std::cout << "Estimated integral: " << sum << std::endl;
}
