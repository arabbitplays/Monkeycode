#ifndef MONKEYCODE_HISTORYANALYZER_HPP
#define MONKEYCODE_HISTORYANALYZER_HPP
#include "model/Graph.hpp"
#include "model/TestHistory.hpp"

class HistoryAnalyzer {
    public:
    HistoryAnalyzer() = default;

    void generateAnalysis(const std::shared_ptr<TestHistory> &test_history);
private:
    GraphHandle getCpmGraph(const std::vector<ReportDto> &reports);
    GraphHandle getAccuracyGraph(const std::vector<ReportDto> &reports);

    static constexpr uint32_t REPORT_COUNT_TO_GRAPH = 200;
};

#endif // MONKEYCODE_HISTORYANALYZER_HPP
