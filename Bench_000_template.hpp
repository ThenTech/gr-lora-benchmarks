#ifndef BENCH_000_TEMPLATE_HPP
#define BENCH_000_TEMPLATE_HPP

#include "hayai/hayai.hpp"

#pragma GCC push_options
#pragma GCC optimize ("O0")

#define ELEMENTS    100000

namespace gr {
    namespace lora {

        //////////////////////////////////////////////////////////////////////////////////////////
        ///		functions
        //////////////////////////////////////////////////////////////////////////////////////////

        // Methods

    }
}

class TempFixture : public ::hayai::Fixture {
    public:
        // const

        virtual void SetUp(void) {
            // ctor
        }

        virtual void TearDown(void) {
            // dtor
        }
};

BENCHMARK_F(TempFixture, Method_old, 30, 1) {
    // code
}

#pragma GCC pop_options

#endif // BENCH_000_TEMPLATE_HPP
