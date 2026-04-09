#include "../../include/rendering/GraphRenderer.hpp"

#include "io/ImageWriter.hpp"
#include "rendering/model/Frame.hpp"

#include <algorithm>
#include <cmath>

GraphRenderer::GraphRenderer(const IVec2 &canvas_size) {
    canvas = std::make_shared<Canvas>(canvas_size, Vec3(0.2f));
}

void GraphRenderer::renderGraph(const GraphHandle &graph) {
    std::vector<Vec2> points = convertGraphPointsToCanvasSpace(graph);
    for (uint32_t i = 0; i < points.size() - 1; i++) {
        RenderLine line = {points[i], points[i + 1], 1, primary_dark_color};
        renderLine(line);
    }

    for (uint32_t i = 0; i < points.size(); i++) {
        RenderPoint point = {points[i], 3, primary_light_color};
        renderPoint(point);
    }
}

std::vector<Vec2>
GraphRenderer::convertGraphPointsToCanvasSpace(const GraphHandle &graph) {
    Vec2 margin(50.0f);
    std::vector<Vec2> canvas_points{};
    canvas_points.reserve(graph->points.size());
    Frame frame{Vec2(margin), graph->getExtent()};
    for (const auto &point : graph->points) {
        canvas_points.push_back(frame.convert(
            asVec2(point), asVec2(canvas->extent) - (2 * margin)));
    }
    return canvas_points;
}

void GraphRenderer::renderPoint(const RenderPoint &point) {
    int32_t max_offset = std::ceil(point.radius);
    Vec2 center_pixel = Vec2(std::round(point.pos.x), std::round(point.pos.y));
    for (int32_t dx = -max_offset; dx <= max_offset; dx++) {
        for (int32_t dy = -max_offset; dy <= max_offset; dy++) {
            Vec2 pixel = center_pixel + Vec2(dx, dy);
            Vec2 delta = point.pos - pixel;
            float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
            float alpha = 1.0f - std::clamp(dist - point.radius, 0.0f, 1.0f);

            IVec2 pixel_pos = asIVec2(pixel);
            if (!canvas->isValidPixel(pixel_pos)) {
                continue;
            }
            canvas->setPixel(pixel_pos, point.color, alpha);
        }
    }
}

void GraphRenderer::renderLine(const RenderLine &line) {
    Vec2 delta = line.end - line.start;
    float steps = std::max(std::abs(delta.x), std::abs(delta.y));
    delta = delta / steps;

    Vec2 pos = line.start;
    for (uint32_t i = 0; i < steps; i++) {
        if (line.thickness > 0.0f) {
            RenderPoint point{pos, line.thickness, line.color};
            renderPoint(point);
        } else {
            renderDot(pos, line.color);
        }
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

IVec2 GraphRenderer::asIVec2(Vec2 v) {

    return IVec2{static_cast<int32_t>(std::round(v.x)),
                 static_cast<int32_t>(std::round(v.y))};
}

Vec2 GraphRenderer::asVec2(IVec2 v) {
    return Vec2{static_cast<float>(v.x), static_cast<float>(v.y)};
}