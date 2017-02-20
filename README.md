gr-lora-benchmarks
==================

A benchmarking framework for the LoRa decoder from [gr-lora](https://github.com/Wosser1sProductions/gr-lora/) and it's functions.

Uses [hayai - the C++ benchmarking framework](https://github.com/nickbruun/hayai).

Tests are set up by creating a new header file, including hayai and adding the following MACRO:

```cpp
BENCHMARK(ClassToTest, NameOfBenchmark, <runs>, <iterations>) {
    // Methods from ClassToTest called to measure execution time
}
```
