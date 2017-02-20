TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    hayai/hayai.hpp \
    hayai/hayai_benchmarker.hpp \
    hayai/hayai_clock.hpp \
    hayai/hayai_compatibility.hpp \
    hayai/hayai_console.hpp \
    hayai/hayai_console_outputter.hpp \
    hayai/hayai_default_test_factory.hpp \
    hayai/hayai_fixture.hpp \
    hayai/hayai_json_outputter.hpp \
    hayai/hayai_junit_xml_outputter.hpp \
    hayai/hayai_main.hpp \
    hayai/hayai_outputter.hpp \
    hayai/hayai_test.hpp \
    hayai/hayai_test_descriptor.hpp \
    hayai/hayai_test_factory.hpp \
    hayai/hayai_test_result.hpp \
    Bench_001_ToBinary.hpp \
    Bench_002_Parity.hpp \
    Bench_003_SelectBits.hpp
