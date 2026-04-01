#include "../../include/analysis/TestReportCreator.hpp"

#include <cassert>

std::shared_ptr<Report> TestReportCreator::createReport(const WordSet &word_set,
                                                        Milliseconds time) {
    auto report = std::make_shared<Report>();
    report->time = time;
    report->word_count = word_set.size();

    for (const auto &word_node : word_set) {
        for (const auto &char_node : word_node.char_nodes) {
            if (char_node.state != OVERFLOW) {
                report->char_count++;
            }

            switch (char_node.state) {
            case FALSE:
                report->wrong_char_count++;
                break;
            case OVERFLOW:
                report->extra_char_count++;
                break;
            case JUMPED_OVER:
                report->missing_char_count++;
                break;
            case UNWRITTEN:
                assert(false);
                break;
            case CORRECT:
                break;
            }
        }
    }

    report->correct_char_count = report->char_count - report->wrong_char_count -
                                 report->missing_char_count;
    report->accuracy = static_cast<float>(report->correct_char_count) /
                       static_cast<float>(report->char_count);
    report->cpm = static_cast<float>(report->correct_char_count) * 60000.0f /
                     static_cast<float>(report->time.count());

    return report;
}
