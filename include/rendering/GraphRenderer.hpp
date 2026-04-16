#ifndef MONKEYCODE_GRAPHRENDERER_HPP
#define MONKEYCODE_GRAPHRENDERER_HPP
#include "model/Canvas.hpp"
#include "model/Graph.hpp"
#include "model/RenderObjects.hpp"
#include "util/vectors/IVec2.hpp"

#include <filesystem>

enum GraphRenderMode {
    POINTS = 0,
    LINES = 1,
    BOX_LINES = 2,
};

enum PaletteColor {
    PRIMARY,
    PRIMARY_DARK,
    SECONDARY,
    SECONDARY_DARK,
    TERTIARY,
    TERTIARY_DARK,
    BACKGROUND,
};

class GraphRenderer {
  public:
    GraphRenderer(const IVec2 &canvas_size);

    void renderGraph(const GraphHandle &graph, GraphRenderMode mode,
                     PaletteColor color);
    void renderGraph(const GraphHandle &graph, GraphRenderMode mode,
                     Vec2 graph_extent, PaletteColor color);
    std::vector<Vec2> convertGraphPointsToCanvasSpace(const GraphHandle &graph,
                                                      Vec2 graph_extent);
    void outputCanvas(const std::filesystem::path &output_path);
    IVec2 asIVec2(Vec2 v);
    Vec2 asVec2(IVec2 v);

  private:
    void renderPoint(const RenderPoint &point);
    void renderLine(const RenderLine &line);
    void renderDot(const Vec2 &pos, const Color &color);
    IVec2 clampToCanvas(IVec2 point);

    Color getPaletteColor(const PaletteColor &color);

    CanvasHandle canvas;

    // https://lospec.com/palette-list/elixir
    const Color primary_dark_color = ColorUtil::fromHexString("#9c4ab5");
    const Color primary_light_color = ColorUtil::fromHexString("#b185d1");
    const Color secondary_dark_color = ColorUtil::fromHexString("#430f40");
    const Color secondary_light_color = ColorUtil::fromHexString("#733060");
};

#endif // MONKEYCODE_GRAPHRENDERER_HPP
