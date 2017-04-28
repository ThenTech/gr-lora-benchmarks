#include <iostream>

#include "hayai/hayai_main.hpp"

//#include "Bench_001_ToBinary.hpp"
//#include "Bench_002_Parity.hpp"
//#include "Bench_003_SelectBits.hpp"
//#include "Bench_004_ReverseVector.hpp"
#include "Bench_005_Accumulate.hpp"
//#include "Bench_006_Volk.hpp"

//#define W_ARGS
//#define JUXML

int main(int argc, char *argv[]) {
    #ifndef W_ARGS
        (void) argc; (void) argv;

        std::cout << "Start benchmark..." << std::endl;

        #ifdef JUXML
            hayai::JUnitXmlOutputter ju(std::cout);
            hayai::Benchmarker::AddOutputter(ju);
        #else
            hayai::ConsoleOutputter consoleOutputter;
            hayai::Benchmarker::AddOutputter(consoleOutputter);
        #endif

        hayai::Benchmarker::RunAllTests();

        return 0;
    #else
        hayai::MainRunner runner;

        int result = runner.ParseArgs(argc, argv);

        if (result) return result;

        return runner.Run();
    #endif
}
