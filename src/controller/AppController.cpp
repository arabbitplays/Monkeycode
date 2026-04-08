#include "../../include/controller/AppController.hpp"

#include "analysis/TestReportCreator.hpp"
#include "generator/ExpressionGenerator.hpp"
#include "io/ReportPrinter.hpp"
#include "io/TestHistoryLoader.hpp"
#include "model/CppCodingExpressions.hpp"
#include "runner/TestRunner.hpp"

AppController::AppController() {
    init();
}

void AppController::init() {
    history_file = "../resources/history.csv";
}

void AppController::executeTest() {
    std::shared_ptr<Expression> start = std::make_shared<StartExpression>();
    std::string generated_text = start->eval();
    TestRunner runner(generated_text);
    runner.run();

    TestReportCreator test_report_creator{};
    std::shared_ptr<Report> test_report = test_report_creator.createReport(
        runner.getWordSet(), runner.getDuration());

    ReportPrinter printer{};
    printer.printTestReport(test_report);
    printer.storeTestResult(history_file, test_report);
}
void AppController::renderHistoryAnalysis() {
    TestHistoryLoader loader(history_file);
    std::shared_ptr<TestHistory> history = loader.load();

}