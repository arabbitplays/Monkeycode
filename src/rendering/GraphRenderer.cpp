#include "../../include/rendering/GraphRenderer.hpp"

#include "io/ImageWriter.hpp"

#include <cmath>

GraphRenderer::GraphRenderer(const IVec2 &canvas_size) {
    canvas = std::make_shared<Canvas>(canvas_size, Vec3(0.2f));
}

void GraphRenderer::renderGraph(const GraphHandle &graph) {
    Color color = Vec3(0.8, 0, 0);
    std::vector<Vec2> points = convertGraphPointsToCanvasSpace(graph);
    for (uint32_t i = 0; i < points.size() - 1; i++) {
        Line line = {points[i], points[i + 1], 1, color};
        renderLine(line);
    }
}

std::vector<Vec2>
GraphRenderer::convertGraphPointsToCanvasSpace(const GraphHandle &graph) {
    Vec2 graph_extent = graph->getExtent();
    std::vector<Vec2> canvas_points{};
    canvas_points.reserve(graph->points.size());
    for (const auto &point : graph->points) {
        canvas_points.emplace_back(
            static_cast<float>(point.x) / graph_extent.x *
                static_cast<float>(canvas->extent.x - 1),
            static_cast<float>(point.y) / graph_extent.y *
                static_cast<float>(canvas->extent.y - 1));
    }
    return canvas_points;
}

void GraphRenderer::renderLine(const Line &line) {
    Vec2 delta = line.end - line.start;
    float steps = std::max(std::abs(delta.x), std::abs(delta.y));
    delta = delta / steps;

    Vec2 pos = line.start;
    for (uint32_t i = 0; i < steps; i++) {
        renderDot(pos, line.color);
        pos = pos + delta;
    }
}

void GraphRenderer::renderDot(const Vec2 &pos, const Color &color) {
    int x = static_cast<int>(std::floor(pos.x));
    int y = static_cast<int>(std::floor(pos.y));

    float fx = pos.x - x;
    float fy = pos.y - y;

    float w00 = (1.0f - fx) * (1.0f - fy);
    float w10 = fx * (1.0f - fy);
    float w01 = (1.0f - fx) * fy;
    float w11 = fx * fy;

    canvas->setPixel(clampToCanvas({x, y}), color, w00);
    canvas->setPixel(clampToCanvas({x + 1, y}), color, w10);
    canvas->setPixel(clampToCanvas({x, y + 1}), color, w01);
    canvas->setPixel(clampToCanvas({x + 1, y + 1}), color, w11);
}

IVec2 GraphRenderer::clampToCanvas(IVec2 point) {
    return IVec2::Clamp(point, {0, 0},
                       {canvas->extent.x - 1, canvas->extent.y - 1});
}

void GraphRenderer::outputCanvas(const std::filesystem::path &output_path) {
    std::filesystem::path output_file = output_path / "graph.ppm";
    ImageWriter::writePPM(output_file, canvas->pixels, canvas->extent);
}