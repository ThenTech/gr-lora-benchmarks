#ifndef BENCH_006_VOLK_HPP
#define BENCH_006_VOLK_HPP

#include <vector>
#include <numeric>
#include <cassert>
#include <cmath>

#include <volk/volk.h>

#include "hayai/hayai.hpp"

#pragma GCC push_options
#pragma GCC optimize ("O0")

#define ELEMENTS    2000000

class VolkFixture : public ::hayai::Fixture {
    public:

        float *test_values_1;
        float *test_values_2;

        virtual void SetUp(void) {
            test_values_1 = new float[ELEMENTS]();
            test_values_2 = new float[ELEMENTS]();

            for (int i = ELEMENTS; i--; ) {
                test_values_1[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                test_values_2[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            }
        }

        virtual void TearDown(void) {
            delete[] test_values_1;
            delete[] test_values_2;
        }
};

/**
 *	Windows TDM-GCC: ?      vs  Arch GCC: 5
 */
BENCHMARK_F(VolkFixture, FloatArray, 10, 100) {
    float *result = new float[ELEMENTS]();

    for (int i = ELEMENTS; i--; )
        result[i] = test_values_1[i] * test_values_2[i];

    assert(result[0] != result[ELEMENTS - 1]);

    delete[] result;
}

BENCHMARK_F(VolkFixture, FloatMul, 10, 100) {
    float *result = new float[ELEMENTS]();

    volk_32f_x2_multiply_32f(result, test_values_1, test_values_2, ELEMENTS);

    assert(result[0] != result[ELEMENTS - 1]);
    delete[] result;
}




#pragma GCC pop_options

#endif // BENCH_006_VOLK_HPP
