#include <iostream>

#include "hayai/hayai_main.hpp"

#include "Bench_001_ToBinary.hpp"
#include "Bench_002_Parity.hpp"
#include "Bench_003_SelectBits.hpp"

/**
 *	<?xml version="1.0" encoding="UTF-8"?>
 *	<testsuites>
 *		<testsuite name="ParityFixture" tests="5">
 *			<testcase name="ParityFixture.Method_old" time="0.011975092" />
 *			<testcase name="ParityFixture.Method_000" time="0.005416040" />
 *			<testcase name="ParityFixture.Method_001" time="0.007241798" />
 *			<testcase name="ParityFixture.Method_002" time="0.000829868" />
 *			<testcase name="ParityFixture.Method_003" time="0.001100964" />
 *		</testsuite>
 *		<testsuite name="SelectBitsFixture" tests="4">
 *			<testcase name="SelectBitsFixture.Method_old" time="0.064890323" />
 *			<testcase name="SelectBitsFixture.Method_000" time="0.002934677" />
 *			<testcase name="SelectBitsFixture.Method_001" time="0.000591144" />
 *			<testcase name="SelectBitsFixture.Method_002" time="0.000454007" />
 *		</testsuite>
 *		<testsuite name="ToBinaryFixture" tests="4">
 *			<testcase name="ToBinaryFixture.Method_old" time="0.221336970" />
 *			<testcase name="ToBinaryFixture.Method_000" time="0.058094315" />
 *			<testcase name="ToBinaryFixture.Method_001" time="0.059668653" />
 *			<testcase name="ToBinaryFixture.Method_002" time="0.021458267" />
 *		</testsuite>
 *	</testsuites>
 */

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
