#include "../../include/rendering/GraphRenderer.hpp"

#include "io/ImageWriter.hpp"

GraphRenderer::GraphRenderer(const IVec2 &canvas_size) {
    canvas = std::make_shared<Canvas>(canvas_size, Vec3(0.2f));
}

void GraphRenderer::renderGraph(GraphHandle graph) {

}

void GraphRenderer::outputCanvas(const std::filesystem::path &output_path) {
    std::filesystem::path output_file = output_path / "graph.ppm";
    ImageWriter::writePPM(output_file, canvas->pixels, canvas->extent);
}
