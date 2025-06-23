#include <chrono>
#include <iostream>
#include <random>
#include "../tiny_tracer.hpp"
#include "monte_carlo.hpp"

void monte_carlo_integral_uniform(float a, float b, int num_samples) {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> distribution(a, b);

    // Estimates the integral of f(x) = x between a and b using num_samples number of samples.
    float sum = 0;
    VarianceEstimator<float> estimator;

    for (int i = 0; i < num_samples; i++) {
        float x = distribution(generator);
        estimator.Add(x);
        sum += x;
    }

    sum *= (b - a) / static_cast<float>(num_samples);

    std::cout << "Estimated integral: " << sum << std::endl;
    std::cout << "Estimated mean: " << estimator.Mean() << std::endl;
    std::cout << "Estimated variance: " << estimator.Variance() << std::endl;
}

template<typename Float>
void VarianceEstimator<Float>::Add(Float x) {
    ++n;
    Float delta = x - mean;
    mean += delta / n;
    Float delta2 = x - mean;
    S += delta2 * delta;
}

template<typename Float>
Float VarianceEstimator<Float>::Mean() {
    return mean;
}

template<typename Float>
Float VarianceEstimator<Float>::Variance() {
    if (n > 1) {
        return S / (n - 1);
    }
    return 0;
}

template<typename Float>
Float VarianceEstimator<Float>::RelativeVariance() {
    if (n < 1 || mean == 0) return 0;
    return Variance() / Mean();
}

template<typename Float>
void VarianceEstimator<Float>::Merge(const VarianceEstimator<Float> &other) {
    if (other.n == 0) return;

    S = S + other.S + sqrt(other.mean - mean) * n * other.n / (n + other.n);
    mean = (n * mean + other.n * other.mean) / (n + other.n);
    n += other.n;
}
