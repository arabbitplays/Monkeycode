#ifndef MONKEYCODE_CANVAS_HPP
#define MONKEYCODE_CANVAS_HPP
#include "util/vectors/IVec2.hpp"
#include "util/vectors/Vec3.hpp"

#include <cassert>
#include <memory>
#include <vector>

typedef Vec3 Color;

struct Canvas {
    IVec2 extent;
    std::vector<Color> pixels;

    Canvas(const IVec2 &extent, const Color &color) : extent(extent) {
        pixels.resize(extent.x * extent.y);
        fill(color);
    }

    void fill(const Color &color) {
        for (auto &pixel : pixels) {
            pixel = color;
        }
    }

    void setPixel(const IVec2& pos, const Color &color, float alpha = 1.0f) {
        assert(pos.x >= 0 && pos.x < extent.x && pos.y >= 0 && pos.y < extent.y);
        uint32_t idx = (extent.y - pos.y - 1) * extent.x + pos.x;
        pixels[idx] = color * alpha + pixels[idx] * (1.0f - alpha);
    }
};

typedef std::shared_ptr<Canvas> CanvasHandle;

#endif // MONKEYCODE_CANVAS_HPP
