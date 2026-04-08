#ifndef VEC3_HPP
#define VEC3_HPP

#include <stdexcept>
#include <functional>

struct Vec3
{
    float x;
    float y;
    float z;

    Vec3()
        : x(0.0f), y(0.0f), z(0.0f) {}

    Vec3(float x, float y, float z)
        : x(x), y(y), z(z) {}

    Vec3(const Vec3& v)
        : x(v.x), y(v.y), z(v.z) {}

    Vec3(float x) : x(x), y(x), z(x) {}

    friend Vec3 operator+(const Vec3& a, const Vec3& b)
    {
        return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    friend Vec3 operator-(const Vec3& a, const Vec3& b)
    {
        return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    friend Vec3 operator*(const Vec3& v, float s)
    {
        return Vec3(v.x * s, v.y * s, v.z * s);
    }

    friend Vec3 operator*(float s, const Vec3& v)
    {
        return v * s;
    }

    friend Vec3 operator/(const Vec3& v, float s)
    {
        return Vec3(v.x / s, v.y / s, v.z / s);
    }

    static Vec3 Clamp(const Vec3& v, const Vec3& min, const Vec3& max)
    {
        if (min.x > max.x || min.y > max.y || min.z > max.z)
        {
            throw std::invalid_argument("min must be smaller than max");
        }

        Vec3 result = v;

        if (v.x < min.x) result.x = min.x;
        if (v.y < min.y) result.y = min.y;
        if (v.z < min.z) result.z = min.z;

        if (v.x > max.x) result.x = max.x;
        if (v.y > max.y) result.y = max.y;
        if (v.z > max.z) result.z = max.z;

        return result;
    }

    bool operator==(const Vec3& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vec3& other) const
    {
        return !(*this == other);
    }
};

namespace std
{
    template<>
    struct hash<Vec3>
    {
        size_t operator()(const Vec3& v) const noexcept
        {
            size_t h1 = std::hash<float>{}(v.x);
            size_t h2 = std::hash<float>{}(v.y);
            size_t h3 = std::hash<float>{}(v.z);

            size_t seed = h1;
            seed ^= h2 + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
            seed ^= h3 + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
}

#endif