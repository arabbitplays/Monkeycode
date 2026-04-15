#ifndef MONKEYCODE_TESTREPORTCREATER_HPP
#define MONKEYCODE_TESTREPORTCREATER_HPP
#include "model/Report.hpp"
#include "runner/TestRunner.hpp"

#include <memory>

class TestReportCreator {
  public:
    TestReportCreator() = default;

    static std::shared_ptr<Report> createReport(const TestResult &result);
};

#endif // MONKEYCODE_TESTREPORTCREATER_HPP
