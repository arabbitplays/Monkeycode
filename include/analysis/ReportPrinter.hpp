#ifndef MONKEYCODE_REPORTPRINTER_HPP
#define MONKEYCODE_REPORTPRINTER_HPP
#include "model/Report.hpp"

#include <filesystem>
#include <memory>

class ReportPrinter {
    public:
    ReportPrinter() = default;

    void printTestReport(const std::shared_ptr<Report> &report);
    void storeTestResult(const std::filesystem::path &storage_file, const std::shared_ptr<Report> &report);
};

#endif // MONKEYCODE_REPORTPRINTER_HPP
