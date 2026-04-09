#ifndef MONKEYCODE_COLORUTIL_HPP
#define MONKEYCODE_COLORUTIL_HPP
#include "util/vectors/Vec3.hpp"

#include <cassert>

typedef Vec3 Color;

class ColorUtil {
  public:
    static Color fromHexString(std::string hex) {
        assert(!hex.empty());

        if (hex[0] == '#')
            hex = hex.substr(1);

        if (hex.size() != 6)
            throw std::invalid_argument("hex string must be 6 characters");

        int r = std::stoi(hex.substr(0, 2), nullptr, 16);
        int g = std::stoi(hex.substr(2, 2), nullptr, 16);
        int b = std::stoi(hex.substr(4, 2), nullptr, 16);

        return Vec3{r / 255.0f, g / 255.0f, b / 255.0f};
    }
};

#endif // MONKEYCODE_COLORUTIL_HPP
