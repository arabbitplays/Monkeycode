#include "analysis/ReportPrinter.hpp"
#include "analysis/TestReportCreator.hpp"

#include <iostream>
#include <memory>

#include "include/model/CppCodingExpressions.hpp"
#include "runner/TestRunner.hpp"

int main(int argc, char *argv[]) {
    std::shared_ptr<Expression> start = std::make_shared<StartExpression>();
    std::string generated_text = start->eval();
    TestRunner runner(generated_text);
    runner.run();

    TestReportCreator test_report_creator{};
    std::shared_ptr<Report> test_report = test_report_creator.createReport(
        runner.getWordSet(), runner.getDuration());

    ReportPrinter printer{};
    printer.printTestReport(test_report);
    printer.storeTestResult("../resources/history.csv", test_report);
}
