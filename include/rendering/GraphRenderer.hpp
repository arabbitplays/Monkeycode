#ifndef MONKEYCODE_GRAPHRENDERER_HPP
#define MONKEYCODE_GRAPHRENDERER_HPP
#include "model/Canvas.hpp"
#include "model/Graph.hpp"
#include "model/RenderObjects.hpp"
#include "util/vectors/IVec2.hpp"

#include <filesystem>

class GraphRenderer {
  public:
    GraphRenderer(const IVec2 &canvas_size);

    void renderGraph(const GraphHandle &graph);
    std::vector<Vec2> convertGraphPointsToCanvasSpace(const GraphHandle &graph);
    void outputCanvas(const std::filesystem::path &output_path);
  private:
    void renderPoint(const RenderPoint &point);
    void renderLine(const RenderLine &line);
    void renderDot(const Vec2 &pos, const Color &color);
    IVec2 clampToCanvas(IVec2 point);

    CanvasHandle canvas;
};

#endif // MONKEYCODE_GRAPHRENDERER_HPP
