#include "../../include/controller/AppController.hpp"

#include "analysis/HistoryAnalyzer.hpp"
#include "analysis/TestReportCreator.hpp"
#include "generator/ExpressionGenerator.hpp"
#include "io/ReportPrinter.hpp"
#include "io/TestHistoryLoader.hpp"
#include "model/CppCodingExpressions.hpp"
#include "rendering/GraphRenderer.hpp"
#include "runner/TestRunner.hpp"

AppController::AppController() { init(); }

void AppController::init() { history_dir = "../resources/history/"; }

void AppController::executeTest() {
    std::shared_ptr<Expression> start = std::make_shared<StartExpression>();
    std::string generated_text = start->eval();
    TestRunner runner{};
    TestResult result = runner.run(generated_text);

    TestReportCreator test_report_creator{};
    std::shared_ptr<Report> test_report =
        test_report_creator.createReport(result);

    ReportPrinter printer(history_dir);
    printer.printTestReport(test_report);
    printer.storeTestReport(test_report);
}

void AppController::renderHistoryAnalysis() {
    TestHistoryLoader loader(history_dir);
    std::shared_ptr<TestHistory> history = loader.load();

    HistoryAnalyzer history_analyzer{};
    history_analyzer.generateAnalysis(history);
}