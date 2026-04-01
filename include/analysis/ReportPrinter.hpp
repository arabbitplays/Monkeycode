#ifndef MONKEYCODE_REPORTPRINTER_HPP
#define MONKEYCODE_REPORTPRINTER_HPP
#include "model/Report.hpp"

#include <memory>

class ReportPrinter {
    public:
    ReportPrinter() = default;

    void printTestReport(const std::shared_ptr<Report> &report);
};

#endif // MONKEYCODE_REPORTPRINTER_HPP
