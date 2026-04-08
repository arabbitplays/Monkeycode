#ifndef MONKEYCODE_GRAOH_HPP
#define MONKEYCODE_GRAOH_HPP
#include "util/vectors/IVec2.hpp"

#include <memory>
#include <string>
#include <vector>

struct Graph {
    std::string title;
    std::vector<IVec2> points;
};

typedef std::shared_ptr<Graph> GraphHandle;

#endif // MONKEYCODE_GRAOH_HPP
