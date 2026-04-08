#ifndef MONKEYCODE_GRAPHRENDERER_HPP
#define MONKEYCODE_GRAPHRENDERER_HPP
#include "model/Canvas.hpp"
#include "model/Graph.hpp"
#include "util/vectors/IVec2.hpp"

#include <filesystem>

class GraphRenderer {
  public:
    GraphRenderer(const IVec2 &canvas_size);

    void renderGraph(GraphHandle graph);
    void outputCanvas(const std::filesystem::path &output_path);
  private:
    CanvasHandle canvas;
};

#endif // MONKEYCODE_GRAPHRENDERER_HPP
