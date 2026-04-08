#ifndef MONKEYCODE_REPORTDTO_HPP
#define MONKEYCODE_REPORTDTO_HPP
#include <cstdint>
#include <string>

struct ReportDto {
    std::string timestamp;
    float cpm;
    float accuracy;
    uint32_t extra_char_count;
    uint32_t missing_char_count;
};
#endif // MONKEYCODE_REPORTDTO_HPP
