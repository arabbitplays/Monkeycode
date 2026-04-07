#ifndef MONKEYCODE_STRINGUTIL_HPP
#define MONKEYCODE_STRINGUTIL_HPP
#include <algorithm>

class StringUtil {
  public:
    static std::string toUpper(const std::string &input) {
        std::string result = input;

        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::toupper(c); });

        return result;
    }

    static std::string capitalize(const std::string &input) {
        if (input.empty())
            return input;

        std::string result = input;

        result[0] = std::toupper(static_cast<unsigned char>(result[0]));

        for (size_t i = 1; i < result.size(); ++i)
            result[i] = std::tolower(static_cast<unsigned char>(result[i]));

        return result;
    }
};
#endif // MONKEYCODE_STRINGUTIL_HPP
