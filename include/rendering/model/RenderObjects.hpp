#ifndef MONKEYCODE_RENDEROBJECTS_HPP
#define MONKEYCODE_RENDEROBJECTS_HPP
#include "Canvas.hpp"
#include "util/vectors/Vec2.hpp"

struct RenderPoint {
    Vec2 pos;
    float radius;
    Color color;
};

struct Line {
    Vec2 start;
    Vec2 end;
    float thickness;
    Color color;
};
#endif // MONKEYCODE_RENDEROBJECTS_HPP
