#include "../../include/analysis/HistoryAnalyzer.hpp"

GraphHandle
HistoryAnalyzer::getCpmGraph(std::shared_ptr<TestHistory> test_history,
                             uint32_t average_count) {

    GraphHandle graph = std::make_shared<Graph>();
    graph->points.reserve(test_history->reports.size());

    uint32_t x = 0;
    for (const auto& report : test_history->reports) {
        graph->points.emplace_back(x, report.cpm);
        x++;
    }

    return graph;
}

