#include "../../include/controller/AppController.hpp"

#include "analysis/HistoryAnalyzer.hpp"
#include "analysis/TestReportCreator.hpp"
#include "generator/ExpressionGenerator.hpp"
#include "io/ReportPrinter.hpp"
#include "io/TestHistoryLoader.hpp"
#include "model/CppCodingExpressions.hpp"
#include "rendering/GraphRenderer.hpp"
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
    TestRunner runner{};
    TestResult result = runner.run(generated_text);

    TestReportCreator test_report_creator{};
    std::shared_ptr<Report> test_report = test_report_creator.createReport(result);

    ReportPrinter printer{};
    printer.printTestReport(test_report);
    printer.storeTestResult(history_file, test_report);
}
void AppController::renderHistoryAnalysis() {
    TestHistoryLoader loader(history_file);
    std::shared_ptr<TestHistory> history = loader.load();

    HistoryAnalyzer history_analyzer{};
    GraphHandle graph = history_analyzer.getCpmGraph(history);
    GraphHandle maxGraph = history_analyzer.getMaxGraph(graph);
    GraphHandle average_10 = history_analyzer.getAverageGraph(graph, 10);
    GraphHandle average_100 = history_analyzer.getAverageGraph(graph, 100);

    GraphRenderer renderer({1000, 600});
    renderer.renderGraph(maxGraph, BOX_LINES, graph->getExtent(), SECONDARY_DARK );
    renderer.renderGraph(average_10, LINES, graph->getExtent(), PRIMARY_DARK);
    renderer.renderGraph(average_100, LINES, graph->getExtent(), PRIMARY);
    renderer.renderGraph(graph, POINTS, SECONDARY);
    renderer.outputCanvas(".");
}