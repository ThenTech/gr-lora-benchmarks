#ifndef BENCH_001_HPP
#define BENCH_001_HPP

#include <string>
#include <vector>
#include <cmath>
#include <bitset>

#include "hayai/hayai.hpp"

#pragma GCC push_options
#pragma GCC optimize ("O0")

#define ELEMENTS    100000

namespace gr {
    namespace lora {

        //////////////////////////////////////////////////////////////////////////////////////////
        ///		to_bin
        //////////////////////////////////////////////////////////////////////////////////////////

        /**
         *	Windows TDM-GCC: 3      vs  Arch GCC: 3
         */
        template <typename T>
        std::string to_bin_old(T v, int element_len_bits) {
            T mask = 0;
            unsigned int maxpow = element_len_bits;
            std::string result = "";

            for (size_t i = 0; i < maxpow; i++) {
                mask = pow(2, i);

                if ((v & mask) > 0) {
                    result += "1";
                } else {
                    result += "0";
                }
            }

            return result;
        }

        /**
         *	Windows TDM-GCC: 2      vs  Arch GCC: 1
         */
        template <typename T>
        std::string to_bin0(T v, size_t bitwidth) {
            unsigned long long maxpow = bitwidth ? (1ull << (bitwidth - 1)) : 0,
                               mask;

            std::string result = "";

            for (mask = 0x1; mask <= maxpow; mask <<= 1) {
                result += (v & mask) ? "1" : "0";
            }

            return result;
        }

        /**
         *	Windows TDM-GCC: 2.5     vs  Arch GCC: 1.5
         */
        template <typename T>
        std::string to_bin1(T v, size_t bitwidth) {
            unsigned long long mask = bitwidth ? (1ull << (bitwidth - 1)) : 0;

            std::string result = "";

            for (; mask; mask >>= 1) {
                result += (v & mask) ? "1" : "0";
            }

            return result;
        }

        /**
         *	Windows TDM-GCC: 1      vs  Arch GCC: 1.7
         */
        template <size_t bitwidth, class T>
        std::string to_bin2(T v) {
            return std::bitset<bitwidth>((unsigned long long) v).to_string();
        }
    }
}

class ToBinaryFixture : public ::hayai::Fixture {
    public:
        const size_t bitwidth = 32;

        std::vector<size_t> test_values;

        virtual void SetUp(void) {
            test_values.reserve(ELEMENTS);

            for (int i = ELEMENTS; i--; ) {
                // rand() only provides a max of MAX_INT which is 0xFFFF
                test_values.push_back( (rand() & 0xFFFF) | ((rand() & 0xFFFF) << 16) );
            }
        }

        virtual void TearDown(void) {
            test_values.clear();
        }
};

BENCHMARK_F(ToBinaryFixture, Method_old, 20, 1) {
    std::string temp;

    for(auto& bits : test_values)
        temp = gr::lora::to_bin_old(bits, this->bitwidth);
}

BENCHMARK_F(ToBinaryFixture, Method_000, 20, 1) {
    std::string temp;

    for(auto& bits : test_values)
        temp = gr::lora::to_bin0(bits, this->bitwidth);
}

BENCHMARK_F(ToBinaryFixture, Method_001, 20, 1) {
    std::string temp;

    for(auto& bits : test_values)
        temp = gr::lora::to_bin1(bits, this->bitwidth);
}

BENCHMARK_F(ToBinaryFixture, Method_002, 20, 1) {
    std::string temp;

    for(auto& bits : test_values)
        temp = gr::lora::to_bin2<32>(bits);
}

#pragma GCC pop_options
#endif // BENCH_001_HPP
