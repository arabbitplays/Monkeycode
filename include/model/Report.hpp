#ifndef MONKEYCODE_REPORT_HPP
#define MONKEYCODE_REPORT_HPP
#include "util/TimeUtil.hpp"

struct Report {
    TimePoint time_stamp;
    Milliseconds duration;
    uint32_t char_count = 0, word_count = 0;
    uint32_t correct_char_count = 0;
    uint32_t extra_char_count = 0, missing_char_count = 0;
    uint32_t wrong_char_count = 0;

    float accuracy = 0, cpm = 0;
};

#endif // MONKEYCODE_REPORT_HPP
