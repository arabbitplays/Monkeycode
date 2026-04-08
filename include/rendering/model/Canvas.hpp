#ifndef MONKEYCODE_CANVAS_HPP
#define MONKEYCODE_CANVAS_HPP
#include "util/vectors/IVec2.hpp"
#include "util/vectors/Vec3.hpp"

#include <memory>
#include <vector>

typedef Vec3 Color;

struct Canvas {
    IVec2 extent;
    std::vector<Color> pixels;

    Canvas(const IVec2 &extent, const Vec3 &color) : extent(extent) {
        pixels.resize(extent.x * extent.y);
        fill(color);
    }

    void fill(const Vec3 &color) {
        for (auto &pixel : pixels) {
            pixel = color;
        }
    }
};

typedef std::shared_ptr<Canvas> CanvasHandle;

#endif // MONKEYCODE_CANVAS_HPP
