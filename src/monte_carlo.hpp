#pragma once

#include "../tiny_tracer.hpp"
#include <cstdint>

void monte_carlo_integral_uniform(float a, float b, int num_samples);

template <typename Float = Float> // A template with a typename float. By default it is set to Float from main.hhp
class VarianceEstimator {
    // A class for computing sample variance using online methods (i.e, without storing all the samples)
    // This is done using Welford's algorithm.

public:
    void Add(Float x);
    Float Mean();
    Float Variance();
    Float RelativeVariance();
    void Merge(const VarianceEstimator<Float>& other);

    private:
    Float mean = 0;
    Float S = 0;
    int64_t n = 0; // Num samples
};


