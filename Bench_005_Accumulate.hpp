#ifndef BENCH_000_ACCUMULATE_HPP
#define BENCH_000_ACCUMULATE_HPP

#include <vector>
#include <numeric>
#include <cassert>
#include <cmath>

#include "hayai/hayai.hpp"

#pragma GCC push_options
#pragma GCC optimize ("O0")

#define ELEMENTS    2000000

inline bool epsilon_equals(double x, double y, double epsilon = 1e-4) {
    return std::abs(x - y) < epsilon;
}

class AccumulateFixture : public ::hayai::Fixture {
    public:

        float *test_values;
        float sumF;

        virtual void SetUp(void) {
            test_values = new float[ELEMENTS]();
            sumF = 0.0f;

            for (int i = ELEMENTS; i--; ) {
                sumF += (test_values[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
            }

            sumF /= ELEMENTS;
        }

        virtual void TearDown(void) {
            delete[] test_values;
        }
};

/**
 *	Windows TDM-GCC: ?      vs  Arch GCC: 5
 */
BENCHMARK_F(AccumulateFixture, Method_for, 10, 100) {
    float sum = 0.0;

    for (int i = ELEMENTS; i--; )
        sum += test_values[i];

    sum /= ELEMENTS;

    assert(epsilon_equals(sum, sumF));
}

/**
 *	Windows TDM-GCC: ?      vs  Arch GCC: 4
 */
BENCHMARK_F(AccumulateFixture, Method_forDefault, 10, 100) {
    float sum = 0.0;

    for (int i = 0; i < ELEMENTS; ++i)
        sum += test_values[i];

    sum /= ELEMENTS;

    assert(epsilon_equals(sum, sumF));
}

/**
 *	Windows TDM-GCC: ?      vs  Arch GCC: 3
 */
BENCHMARK_F(AccumulateFixture, Method_while, 10, 100) {
    float sum = 0.0;
    int i = ELEMENTS;

    while (i--)
        sum += test_values[i];

    sum /= ELEMENTS;

    assert(epsilon_equals(sum, sumF));
}

/**
 *	Windows TDM-GCC: ?      vs  Arch GCC: 2
 */
BENCHMARK_F(AccumulateFixture, Method_whileGr, 10, 100) {
    float sum = 0.0;
    int i = ELEMENTS;

    while (i-- >= 0)
        sum += test_values[i];

    sum /= ELEMENTS;

    assert(epsilon_equals(sum, sumF));
}

/**
 *	Windows TDM-GCC: ?      vs  Arch GCC: 1.01
 */
BENCHMARK_F(AccumulateFixture, Method_AccuD, 10, 100) {
    double sum = std::accumulate(test_values, test_values + ELEMENTS, 0.0) / ELEMENTS;

    assert(epsilon_equals(sum, sumF));
}

/**
 *	Windows TDM-GCC: ?      vs  Arch GCC: 1
 */
BENCHMARK_F(AccumulateFixture, Method_AccuF, 10, 100) {
    float sum = std::accumulate(test_values, test_values + ELEMENTS, 0.0f) / ELEMENTS;

    assert(epsilon_equals(sum, sumF));
}

#pragma GCC pop_options

#endif // BENCH_000_ACCUMULATE_HPP
