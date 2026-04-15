#ifndef VEC2_HPP
#define VEC2_HPP

#include <stdexcept>
#include <functional>

struct Vec2
{
    float x;
    float y;

    Vec2()
        : x(0.0f), y(0.0f) {}

    Vec2(const float x, const float y)
        : x(x), y(y) {}

    explicit Vec2(const float x) : x(x), y(x) {}

    friend Vec2 operator+(const Vec2& a, const Vec2& b)
    {
        return {a.x + b.x, a.y + b.y};
    }

    friend Vec2 operator-(const Vec2& a, const Vec2& b)
    {
        return {a.x - b.x, a.y - b.y};
    }

    friend Vec2 operator*(const Vec2& v, float s)
    {
        return {v.x * s, v.y * s};
    }

    friend Vec2 operator*(float s, const Vec2& v)
    {
        return v * s;
    }

    friend Vec2 operator/(const Vec2& v, float s)
    {
        return {v.x / s, v.y / s};
    }

    static Vec2 Clamp(const Vec2& v, const Vec2& min, const Vec2& max)
    {
        if (min.x > max.x || min.y > max.y)
        {
            throw std::invalid_argument("min must be smaller than max");
        }

        Vec2 result = v;

        if (v.x < min.x) result.x = min.x;
        if (v.y < min.y) result.y = min.y;

        if (v.x > max.x) result.x = max.x;
        if (v.y > max.y) result.y = max.y;

        return result;
    }

    bool operator==(const Vec2& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2& other) const
    {
        return !(*this == other);
    }
};

namespace std
{
    template<>
    struct hash<Vec2>
    {
        size_t operator()(const Vec2& v) const noexcept
        {
            size_t h1 = std::hash<float>{}(v.x);
            size_t h2 = std::hash<float>{}(v.y);

            size_t seed = h1;
            seed ^= h2 + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
}

#endif