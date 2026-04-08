#include "../../include/io/ReportPrinter.hpp"

#include "model/ReportDto.hpp"

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

    std::cout << "Accuracy:         " << report->accuracy * 100.0F << "%"
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

    ReportDto dto{
        TimeUtil::formatTimePoint(report->time_stamp),
        report->cpm,
        report->accuracy,
        report->extra_char_count,
        report->missing_char_count,
    };

    writeReportDto(std::move(file), dto);
}

void ReportPrinter::writeReportDto(std::ofstream file, ReportDto& report) {
    file << report.timestamp << "," << report.cpm << "," << report.accuracy << ","
         << report.extra_char_count << "," << report.missing_char_count
         << "\n";
}