#ifndef MONKEYCODE_REPORTPRINTER_HPP
#define MONKEYCODE_REPORTPRINTER_HPP
#include "model/Report.hpp"
#include "model/ReportDto.hpp"

#include <filesystem>
#include <memory>

class ReportPrinter {
  public:
    ReportPrinter() = default;

    static void printTestReport(const std::shared_ptr<Report> &report);
    static void storeTestResult(const std::filesystem::path &storage_file,
                                const std::shared_ptr<Report> &report);

  private:
    static void writeReportDto(std::ofstream file, ReportDto &dto);
};

#endif // MONKEYCODE_REPORTPRINTER_HPP
