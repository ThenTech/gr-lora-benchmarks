#ifndef BENCH_002_PARITY_HPP
#define BENCH_002_PARITY_HPP

#include <bitset>

#include "hayai/hayai.hpp"

#pragma GCC push_options
#pragma GCC optimize ("O0")

#define ELEMENTS    100000


namespace gr {
    namespace lora {
        /////////////////////////////////////////////////////////////////////////////////////////
        ///		check_parity
        //////////////////////////////////////////////////////////////////////////////////////////

		/**
		 *	5
		 */
        bool check_parity_old(std::string word, bool even = true) {
            int count = 0;

            for (int i = 0; i < 7; i++) {
                if (word[i] == '1')
                    count += 1;
            }

            if (even) return ((count % 2) == 0);
            else	  return (((count + 1) % 2) == 0);
        }

		/**
		 *	3
		 */
        bool check_parity0(std::string& word, bool even = true) {
            size_t count = 0, i = 0;

            while(i < 7) {
                if (word[i++] == '1')
                    ++count;
            }

            return (count & 0x1) == (even ? 0 : 1);
        }

		/**
		 *	4
		 */
        bool check_parity1(unsigned long long word, bool even = true) {
            // Copy and shifting is still slow
            size_t count = 0;

            while(word) {
                count ^= word;
                word >>= 1;
            }

            return (count & 0x1) == (even ? 0 : 1);
        }

		/**
		 *	1 FASTEST
		 */
        bool check_parity2(unsigned long long word, bool even = true) {
            word ^= word >> 1;
            word ^= word >> 2;
            word = (word & 0x1111111111111111UL) * 0x1111111111111111UL;

            return ((word >> 60) & 1) == (even ? 0 : 1);
        }

		/**
		 *	2
		 */
        template <size_t bitwidth>
        bool check_parity3(unsigned long long word, bool even = true) {
            return (std::bitset<bitwidth>(word).count() & 0x1) == (even ? 0 : 1);
        }
    }
}

class ParityFixture : public ::hayai::Fixture {
    public:
        const size_t bitwidth = 32;

        std::vector<size_t> test_values;
        std::vector<std::string> test_strings;

        virtual void SetUp(void) {
            test_values.reserve(ELEMENTS);
            test_strings.reserve(ELEMENTS);

            for (int i = ELEMENTS; i--; ) {
                // rand() only provides a max of MAX_INT which is 0xFFFF
                size_t tmp = (rand() & 0xFFFF) | ((rand() & 0xFFFF) << 16);
                test_values.push_back( (rand() & 0xFFFF) | ((rand() & 0xFFFF) << 16) );
                test_strings.push_back( std::bitset<32>(tmp).to_string() );
            }
        }

        virtual void TearDown(void) {
            test_values.clear();
            test_strings.clear();
        }
};

BENCHMARK_F(ParityFixture, Method_old, 25, 1) {
    bool temp;

    for(auto& bits : test_strings)
        temp = gr::lora::check_parity_old(bits) | temp;
}

BENCHMARK_F(ParityFixture, Method_000, 25, 1) {
    bool temp;

    for(auto& bits : test_strings)
        temp = gr::lora::check_parity0(bits) | temp;
}

BENCHMARK_F(ParityFixture, Method_001, 25, 1) {
    bool temp;

    for(auto& bits : test_values)
        temp = gr::lora::check_parity1(bits) | temp;
}

BENCHMARK_F(ParityFixture, Method_002, 25, 1) {
    bool temp;

    for(auto& bits : test_values)
        temp = gr::lora::check_parity2(bits) | temp;
}

BENCHMARK_F(ParityFixture, Method_003, 25, 1) {
    bool temp;

    for(auto& bits : test_values)
        temp = gr::lora::check_parity3<32>(bits) | temp;
}

#pragma GCC pop_options
#endif // BENCH_002_PARITY_HPP
