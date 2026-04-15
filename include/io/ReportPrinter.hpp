#ifndef MONKEYCODE_REPORTPRINTER_HPP
#define MONKEYCODE_REPORTPRINTER_HPP
#include "model/Report.hpp"
#include "model/ReportDto.hpp"

#include <filesystem>
#include <memory>

class ReportPrinter {
  public:
    explicit ReportPrinter(std::filesystem::path storage_path);

    static void printTestReport(const std::shared_ptr<Report> &report);
    void storeTestReport(const std::shared_ptr<Report> &report);
    void writeHeaderLine(std::ofstream &file);

  private:
    void writeReportDto(std::ofstream file, ReportDto &dto);
    std::ofstream getCurrHistoryFile();

    const size_t MAX_HISTORY_FILE_LINES = 501;
    std::filesystem::path storage_path;
};

#endif // MONKEYCODE_REPORTPRINTER_HPP
