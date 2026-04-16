#include "../../include/io/ReportPrinter.hpp"

#include "model/ReportDto.hpp"
#include "rendering/util/HistoryUtil.hpp"

#include <fstream>
#include <iostream>
#include <utility>

ReportPrinter::ReportPrinter(std::filesystem::path storage_path)
    : storage_path(std::move(storage_path)) {
    std::filesystem::create_directories(this->storage_path);
}

void ReportPrinter::printTestReport(const std::shared_ptr<Report> &report) {
    std::cout << "########################\n";
    std::cout << "#     Test Results     #\n";
    std::cout << "########################\n";
    std::cout << std::endl;

    std::cout << "Chars per minute: " << report->cpm << std::endl;
    std::cout << "Accuracy:         " << report->accuracy * 100.0F << "%"
              << std::endl;

    std::cout << "Correct chars:    " << report->correct_char_count
              << std::endl;
    std::cout << "Extra chars:      " << report->extra_char_count << std::endl;
    std::cout << "Missing chars:    " << report->missing_char_count
              << std::endl;
}

void ReportPrinter::storeTestReport(const std::shared_ptr<Report> &report) {
    std::ofstream file = getCurrHistoryFile();
    ReportDto dto{
        TimeUtil::formatTimePoint(report->time_stamp),
        report->cpm,
        report->accuracy,
        report->extra_char_count,
        report->missing_char_count,
    };

    writeReportDto(std::move(file), dto);
}

void ReportPrinter::writeHeaderLine(std::ofstream &file) {
    file << "Timestamp,CPM,Accuracy,Extra Chars,Missing Chars\n";
}

void ReportPrinter::writeReportDto(std::ofstream file, ReportDto &report) {
    file << report.timestamp << "," << report.cpm << "," << report.accuracy
         << "," << report.extra_char_count << "," << report.missing_char_count
         << "\n";
}

std::ofstream ReportPrinter::getCurrHistoryFile() {
    int32_t curr_file_index = -1;
    std::filesystem::path curr_file_path = "";
    for (const auto &entry :
         std::filesystem::directory_iterator(storage_path)) {
        if (entry.is_regular_file()) {
            int32_t file_index = HistoryUtil::extractFileIndex(entry.path().stem().string());
            if (file_index > curr_file_index) {
                curr_file_index = file_index;
                curr_file_path = entry.path();
            }
        }
    }

    if (curr_file_path.empty() ||
        HistoryUtil::countLines(curr_file_path) >= MAX_HISTORY_FILE_LINES) {

        auto file = HistoryUtil::createNewHistoryFile(storage_path, curr_file_index + 1);
        writeHeaderLine(file);
        return file;
    }

    std::ofstream file(curr_file_path, std::ios::app);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    return file;
}
