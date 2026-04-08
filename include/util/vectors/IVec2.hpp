#ifndef IVEC2_HPP
#define IVEC2_HPP

#include <functional>
#include <stdexcept>

struct IVec2 {
    int x;
    int y;

    IVec2() : x(0), y(0) {}

    IVec2(int x, int y) : x(x), y(y) {}

    IVec2(const IVec2 &v) : x(v.x), y(v.y) {}

    friend IVec2 operator+(const IVec2 &a, const IVec2 &b) {
        return IVec2(a.x + b.x, a.y + b.y);
    }

    friend IVec2 operator-(const IVec2 &a, const IVec2 &b) {
        return IVec2(a.x - b.x, a.y - b.y);
    }

    static IVec2 Clamp(const IVec2 &v, const IVec2 &min, const IVec2 &max) {
        if (min.x > max.x || min.y > max.y) {
            throw std::invalid_argument("min must be smaller than max");
        }

        IVec2 result = v;

        if (v.x < min.x)
            result.x = min.x;
        if (v.y < min.y)
            result.y = min.y;

        if (v.x > max.x)
            result.x = max.x;
        if (v.y > max.y)
            result.y = max.y;

        return result;
    }

    bool operator==(const IVec2 &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const IVec2 &other) const { return !(*this == other); }
};

namespace std {
template <> struct hash<IVec2> {
    size_t operator()(const IVec2 &v) const noexcept {
        size_t h1 = std::hash<int>{}(v.x);
        size_t h2 = std::hash<int>{}(v.y);
        return h1 ^ (h2 << 1);
    }
};
} // namespace std

#endif