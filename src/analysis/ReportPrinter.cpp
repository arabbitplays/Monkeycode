#include "../../include/analysis/ReportPrinter.hpp"

#include <iostream>

void ReportPrinter::printTestReport(const std::shared_ptr<Report> &report) {
    std::cout << "########################\n";
    std::cout << "#     Test Results     #\n";
    std::cout << "########################\n";
    std::cout << std::endl;

    uint32_t correct_char_count = report->char_count -
                                  report->wrong_char_count -
                                  report->missing_char_count;

    std::cout << "Correct chars:    " << correct_char_count << std::endl;
    std::cout << "Chars per minute: "
              << static_cast<float>(correct_char_count) * 60000.0f /
                     static_cast<float>(report->time.count())
              << std::endl;
    std::cout << "Extra chars:      " << report->extra_char_count << std::endl;

    std::cout << "Accuracy:         "
              << static_cast<float>(correct_char_count) /
                     static_cast<float>(report->char_count) * 100.0f
              << "%" << std::endl;
    std::cout << "Extra chars:      " << report->extra_char_count << std::endl;
    std::cout << "Missing chars:    " << report->missing_char_count
              << std::endl;
}
