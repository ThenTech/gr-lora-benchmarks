#include <iostream>

#include "hayai/hayai_main.hpp"

//#include "Bench_001_ToBinary.hpp"
//#include "Bench_002_Parity.hpp"
#include "Bench_003_SelectBits.hpp"

//#define W_ARGS

int main(int argc, char *argv[]) {
    #ifndef W_ARGS
        std::cout << "Start benchmark..." << std::endl;

//        hayai::ConsoleOutputter consoleOutputter;
//        hayai::Benchmarker::AddOutputter(consoleOutputter);

        hayai::JUnitXmlOutputter ju(std::cout);
        hayai::Benchmarker::AddOutputter(ju);

        hayai::Benchmarker::RunAllTests();

        return 0;
    #else
        hayai::MainRunner runner;

        int result = runner.ParseArgs(argc, argv);

        if (result) return result;

        return runner.Run();
    #endif
}
