#ifndef MONKEYCODE_HISTORYANALYZER_HPP
#define MONKEYCODE_HISTORYANALYZER_HPP
#include "model/Graph.hpp"
#include "model/TestHistory.hpp"

class HistoryAnalyzer {
    public:
    HistoryAnalyzer() = default;

    GraphHandle getCpmGraph(const std::shared_ptr<TestHistory> &test_history);
    GraphHandle getAverageGraph(GraphHandle graph, uint32_t average_count);
    GraphHandle getMaxGraph(GraphHandle graph);

private:
    static constexpr uint32_t REPORT_COUNT_TO_GRAPH = 200;
};

#endif // MONKEYCODE_HISTORYANALYZER_HPP
