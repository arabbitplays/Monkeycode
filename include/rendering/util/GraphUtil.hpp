#ifndef MONKEYCODE_GRAPHUTIK_HPP
#define MONKEYCODE_GRAPHUTIK_HPP
#include "model/Graph.hpp"

class GraphUtil {
  public:
    static GraphHandle getAverageGraph(const GraphHandle &graph,
                                const uint32_t average_count) {
        GraphHandle average_graph = std::make_shared<Graph>();
        average_graph->points.reserve(graph->points.size());

        for (uint32_t i = 0; i < graph->points.size(); i++) {
            float sum = 0;
            uint32_t denom = std::min(i + 1, average_count);
            for (uint32_t j = 0; j < average_count; j++) {
                if (j > i) {
                    break;
                }
                sum += graph->points[i - j].y;
            }
            average_graph->points.emplace_back(i,
                                               sum / static_cast<float>(denom));
        }

        return average_graph;
    }

    static GraphHandle getMaxGraph(const GraphHandle &graph) {
        GraphHandle maxGraph = std::make_shared<Graph>();
        float curr_max = graph->points[0].y;
        maxGraph->points.push_back(graph->points[0]);
        for (const auto &point : graph->points) {
            if (point.y > curr_max) {
                curr_max = point.y;
                maxGraph->points.push_back(point);
            }
        }
        maxGraph->points.emplace_back(graph->points[graph->points.size() - 1].x,
                                      curr_max);
        return maxGraph;
    }

    static GraphHandle getMinGraph(const GraphHandle & graph) {
        GraphHandle min_graph = std::make_shared<Graph>();
        float curr_min = graph->points[0].y;
        min_graph->points.push_back(graph->points[0]);
        for (const auto &point : graph->points) {
            if (point.y < curr_min) {
                curr_min = point.y;
                min_graph->points.push_back(point);
            }
        }
        min_graph->points.emplace_back(graph->points[graph->points.size() - 1].x,
                                      curr_min);
        return min_graph;
    }
};

#endif // MONKEYCODE_GRAPHUTIK_HPP
