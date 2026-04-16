#include "../../include/analysis/HistoryAnalyzer.hpp"

#include "rendering/GraphRenderer.hpp"
#include "rendering/util/GraphUtil.hpp"

void HistoryAnalyzer::generateAnalysis(const std::shared_ptr<TestHistory> &test_history) {
    std::vector<ReportDto> reports =
        test_history->reports.size() > REPORT_COUNT_TO_GRAPH
            ? std::vector<ReportDto>(test_history->reports.end() -
                                         REPORT_COUNT_TO_GRAPH,
                                     test_history->reports.end())
            : test_history->reports;

    GraphHandle cpm = getCpmGraph(reports);
    GraphHandle max_cpm = GraphUtil::getMaxGraph(cpm);
    GraphHandle cpm_average_10 = GraphUtil::getAverageGraph(cpm, 10);
    GraphHandle cpm_average_100 = GraphUtil::getAverageGraph(cpm, 100);

    GraphHandle error = getAccuracyGraph(reports);
    GraphHandle min_error = GraphUtil::getMinGraph(error);
    GraphHandle error_average_10 = GraphUtil::getAverageGraph(error, 10);

    GraphRenderer renderer({1000, 600});
    renderer.renderGraph(max_cpm, BOX_LINES, cpm->getExtent(),
                         SECONDARY_DARK);
    renderer.renderGraph(cpm_average_10, LINES, cpm->getExtent(), PRIMARY_DARK);
    renderer.renderGraph(cpm_average_100, LINES, cpm->getExtent(), PRIMARY);

    Vec2 error_graph_extent = error->getExtent();
    error_graph_extent.y = 1;
    renderer.renderGraph(min_error, BOX_LINES, error_graph_extent, TERTIARY);
    renderer.renderGraph(error_average_10, LINES, error_graph_extent, TERTIARY_DARK);

    renderer.renderGraph(cpm, POINTS, SECONDARY);
    renderer.outputCanvas(".");
}

GraphHandle
HistoryAnalyzer::getCpmGraph(const std::vector<ReportDto> &reports) {

    GraphHandle graph = std::make_shared<Graph>();
    graph->points.reserve(reports.size());

    uint32_t x = 0;
    for (const auto &report : reports) {
        graph->points.emplace_back(x, report.cpm);
        x++;
    }

    return graph;
}

GraphHandle HistoryAnalyzer::getAccuracyGraph(
    const std::vector<ReportDto> &reports) {

    GraphHandle graph = std::make_shared<Graph>();
    graph->points.reserve(reports.size());

    uint32_t x = 0;
    for (const auto &report : reports) {
        graph->points.emplace_back(x, 1.0f - report.accuracy);
        x++;
    }

    return graph;
}