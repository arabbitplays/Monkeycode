#ifndef MONKEYCODE_TESTHISTORY_HPP
#define MONKEYCODE_TESTHISTORY_HPP
#include "ReportDto.hpp"

#include <vector>

struct TestHistory {
    std::vector<ReportDto> reports;
};

#endif // MONKEYCODE_TESTHISTORY_HPP
