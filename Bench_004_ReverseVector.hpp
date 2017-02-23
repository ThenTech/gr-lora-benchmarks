#ifndef BENCH_004_REVERSEVECTOR_HPP
#define BENCH_004_REVERSEVECTOR_HPP

#include <vector>
#include <deque>
#include <algorithm>
#include <cassert>

#include "hayai/hayai.hpp"

#pragma GCC push_options
#pragma GCC optimize ("O0")

#define ELEMENTS    1000000

class VectorReverseFixture : public ::hayai::Fixture {
    public:
        // const
        std::vector<size_t> test_values;
        std::vector<size_t> result_values;

        virtual void SetUp(void) {
            test_values.reserve(ELEMENTS);

            for (int i = ELEMENTS; i--; ) {
                test_values.push_back( (rand() & 0xFFFF) | ((rand() & 0xFFFF) << 16) );
            }
        }

        virtual void TearDown(void) {
            test_values.clear();
            result_values.clear();
        }
};

/**
 *	Windows TDM-GCC: ?      vs  Arch GCC: 4
 */
BENCHMARK_F(VectorReverseFixture, Method_forReverse, 10, 25) {
    // push, std::reverse, re push
    std::vector<size_t> v;

    for (size_t& x : test_values)
        v.push_back(x);

    size_t front = v.front(), back = v.back();
    std::reverse(v.begin(), v.end());
    assert(front == v.back());
    assert(back == v.front());

    for (size_t& x : v)
        result_values.push_back(x);

    assert(front == result_values.back());
    assert(back == result_values.front());
    result_values.clear();
}

/**
 *	Windows TDM-GCC: ?      vs  Arch GCC: 1
 */
BENCHMARK_F(VectorReverseFixture, Method_forRevDirect, 10, 25) {
    // push, std::reverse

    for (size_t& x : test_values)
        result_values.push_back(x);

    size_t front = result_values.front(), back = result_values.back();

    std::reverse(result_values.begin(), result_values.end());

    assert(front == result_values.back());
    assert(back == result_values.front());
    result_values.clear();
}

/**
 *	Windows TDM-GCC: ?      vs  Arch GCC: 3
 */
BENCHMARK_F(VectorReverseFixture, Method_forRevIt, 10, 25) {
    // push, reverse assign
    std::vector<size_t> v;

    for (size_t& x : test_values)
        v.push_back(x);

    size_t front = v.front(), back = v.back();

    result_values.assign(v.rbegin(), v.rend());

    assert(front == result_values.back());
    assert(back == result_values.front());
    result_values.clear();
}

/**
 *	Windows TDM-GCC: ?      vs  Arch GCC: 2
 */
BENCHMARK_F(VectorReverseFixture, Method_forDequeIt, 10, 25) {
    // push in deque, assign
    std::deque<size_t> d;

    for (size_t& x : test_values)
        d.push_front(x);

    size_t front = d.front(), back = d.back();

    result_values.assign(d.begin(), d.end());

    assert(front == result_values.front());
    assert(back == result_values.back());
    result_values.clear();
}

/**
 *	Windows TDM-GCC: ?      vs  Arch GCC: 2.1
 */
BENCHMARK_F(VectorReverseFixture, Method_forDequeIns, 10, 25) {
    // push in deque, assign
    std::deque<size_t> d;

    for (size_t& x : test_values)
        d.push_front(x);

    size_t front = d.front(), back = d.back();

    result_values.insert(result_values.end(), d.begin(), d.end());

    assert(front == result_values.front());
    assert(back == result_values.back());
    result_values.clear();
}


#pragma GCC pop_options

#endif // BENCH_004_REVERSEVECTOR_HPP
