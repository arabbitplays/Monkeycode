#ifndef MONKEYCODE_TRANSFORM_HPP
#define MONKEYCODE_TRANSFORM_HPP
#include "util/vectors/Vec2.hpp"

struct Frame {
    Vec2 translation;
    Vec2 extent;

    Vec2 convert(const Vec2 &v, const Vec2 &target_extent) const {
        return translation + Vec2{ v.x / extent.x * target_extent.x, v.y / extent.y * target_extent.y };
    }
};
#endif // MONKEYCODE_TRANSFORM_HPP
