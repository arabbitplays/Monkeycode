#ifndef MONKEYCODE_GRAOH_HPP
#define MONKEYCODE_GRAOH_HPP
#include "util/vectors/IVec2.hpp"
#include "util/vectors/Vec2.hpp"

#include <memory>
#include <string>
#include <vector>

struct Graph {
    std::string title;
    std::vector<IVec2> points;

    Vec2 getExtent() {
        Vec2 min, max;
        for (const auto &point : points) {
            min = {std::min(static_cast<float>(point.x), min.x), std::min(static_cast<float>(point.y), min.y)};
            max = {std::max(static_cast<float>(point.x), max.x), std::max(static_cast<float>(point.y), max.y)};
        }
        return max - min;
    }
};

typedef std::shared_ptr<Graph> GraphHandle;

#endif // MONKEYCODE_GRAOH_HPP
