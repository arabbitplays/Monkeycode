#include "../../include/analysis/ReportPrinter.hpp"

#include <fstream>
#include <iostream>

void ReportPrinter::printTestReport(const std::shared_ptr<Report> &report) {
    std::cout << "########################\n";
    std::cout << "#     Test Results     #\n";
    std::cout << "########################\n";
    std::cout << std::endl;

    std::cout << "Correct chars:    " << report->correct_char_count
              << std::endl;
    std::cout << "Chars per minute: " << report->cpm << std::endl;
    std::cout << "Extra chars:      " << report->extra_char_count << std::endl;

    std::cout << "Accuracy:         " << report->accuracy * 100.0f << "%"
              << std::endl;
    std::cout << "Extra chars:      " << report->extra_char_count << std::endl;
    std::cout << "Missing chars:    " << report->missing_char_count
              << std::endl;
}

void ReportPrinter::storeTestResult(const std::filesystem::path &storage_file,
                                    const std::shared_ptr<Report> &report) {

    std::ofstream file(storage_file, std::ios::app);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    file << report->cpm << "," << report->accuracy << ","
         << report->extra_char_count << "," << report->missing_char_count
         << "\n";
}
