#ifndef BENCH_003_SELECTBITS_HPP
#define BENCH_003_SELECTBITS_HPP

#include <cmath>
#include "hayai/hayai.hpp"

#pragma GCC push_options
#pragma GCC optimize ("O0")

#define ELEMENTS    100000

namespace gr {
    namespace lora {

        //////////////////////////////////////////////////////////////////////////////////////////
        ///		selectBits
        //////////////////////////////////////////////////////////////////////////////////////////

        /**
         *	Windows TDM-GCC: 4      vs  Arch GCC: 4
         */
        uint32_t select_bits_old(uint32_t data, uint8_t* indices, uint8_t n) {
            uint32_t result = 0;

            for(uint32_t j = 0; j < n; j++) {
                uint32_t power = pow(2, indices[j]);
                if((data & power) > 0) {
                    result += pow(2, j);
                }
            }

            return result;
        }

        /**
         *	Windows TDM-GCC: 3 FASTER and correct?    vs  Arch GCC: 3
         */
        uint32_t select_bits_0(uint32_t data, uint8_t* indices, uint8_t n) {
            uint32_t r = 0;

            for(size_t i = 0; i < n; ++i)
                //r |= data & (1 << indices[i]);
                r |= (data & (1 << indices[i])) ? (1 << i) : 0;

            return r;
        }

        /**
         *	Windows TDM-GCC: 1 FASTEST   vs  Arch GCC: 1
         */
        typedef enum SELECT_BITS {
            BIT0  = 0x0001, BIT1  = 0x0002, BIT2  = 0x0004, BIT3  = 0x0008,
            BIT4  = 0x0010, BIT5  = 0x0020, BIT6  = 0x0040, BIT7  = 0x0080,
            BIT8  = 0x0100, BIT9  = 0x0200, BIT10 = 0x0400, BIT11 = 0x0800,
            BIT12 = 0x1000, BIT13 = 0x2000, BIT14 = 0x4000, BIT15 = 0x8000
        //            BIT16 ,    BIT17, BIT18, BIT19, BIT20, BIT21, BIT22, BIT23,
        //            BIT24 ,    BIT25, BIT26, BIT27, BIT28, BIT29, BIT30, BIT31
        } SELECT_BITS;

        /**
         *	Windows TDM-GCC: 2    vs  Arch GCC: 2
         */
        inline uint32_t select_bits_1(uint32_t data, uint32_t mask) {
            return data & mask;
        }

        /**
         *	Windows TDM-GCC: 1    vs  Arch GCC: 1
         */
        #define select_bits_2(data, mask)   ((data) & (mask))

    }
}

class SelectBitsFixture : public ::hayai::Fixture {
    public:
        const size_t bitwidth = 32;

        std::vector<uint8_t*> test_values;
        std::vector<uint32_t> test_masks;

        virtual void SetUp(void) {
            test_values.reserve(ELEMENTS);
            test_masks.reserve(ELEMENTS);

            for (int i = ELEMENTS; i--; ) {
                uint8_t *tmp = new uint8_t[8]();
                uint32_t mask = 0;

                for (int i = 8; --i; ) {
                    tmp[i] = (rand() % 16) & 0xF;
                    mask |= (1 << tmp[i]);
                }

                test_values.push_back( tmp );
                test_masks.push_back( mask );
            }
        }

        virtual void TearDown(void) {
            for (uint8_t* p : test_values)
                delete[] p;
            test_values.clear();
            test_masks.clear();
        }
};

BENCHMARK_F(SelectBitsFixture, Method_old, 30, 1) {
    uint32_t temp = 0;

    for(auto& bits : test_values)
        temp = gr::lora::select_bits_old(0xFFFF, bits, 8) | temp;
}

BENCHMARK_F(SelectBitsFixture, Method_000, 30, 1) {
    uint32_t temp = 0;

    for(auto& bits : test_values)
        temp = gr::lora::select_bits_0(0xFFFF, bits, 8) | temp;
}

BENCHMARK_F(SelectBitsFixture, Method_001, 30, 1) {
    uint32_t temp = 0;

    for(auto& bits : test_masks)
        temp = gr::lora::select_bits_1(0xFFFF, bits) | temp;
}

BENCHMARK_F(SelectBitsFixture, Method_002, 30, 1) {
    uint32_t temp = 0;

    for(auto& bits : test_masks)
        temp = select_bits_2(0xFFFF, bits) | temp;
}

#pragma GCC pop_options
#endif // BENCH_003_SELECTBITS_HPP
