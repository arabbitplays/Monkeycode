#ifndef MONKEYCODE_TIMEUTIL_HPP
#define MONKEYCODE_TIMEUTIL_HPP
#include <chrono>

typedef std::chrono::milliseconds Milliseconds;
typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>
    TimePoint;

class TimeUtil {
  public:
    static TimePoint getTimeStamp() {
        return std::chrono::floor<std::chrono::seconds>(
            std::chrono::system_clock::now());
    }

    static std::string formatTimePoint(TimePoint time_point) {
        return std::format("{:%Y-%m-%d %H:%M:%S}", time_point);
    }
};
#endif // MONKEYCODE_TIMEUTIL_HPP
