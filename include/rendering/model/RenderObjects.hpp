#ifndef MONKEYCODE_RENDEROBJECTS_HPP
#define MONKEYCODE_RENDEROBJECTS_HPP
#include "util/vectors/IVec2.hpp"

struct RenderPoint {
    IVec2 pos;
    float radius;
};

struct Line {
    IVec2 start;
    IVec2 end;
    float thickness;
};
#endif // MONKEYCODE_RENDEROBJECTS_HPP
