#ifndef MONKEYCODE_HISTORYANALYZER_HPP
#define MONKEYCODE_HISTORYANALYZER_HPP
#include "model/Graph.hpp"
#include "model/TestHistory.hpp"

class HistoryAnalyzer {
    public:
    HistoryAnalyzer() = default;

    GraphHandle getCpmGraph(std::shared_ptr<TestHistory> test_history, uint32_t average_count = 1);
};

#endif // MONKEYCODE_HISTORYANALYZER_HPP
