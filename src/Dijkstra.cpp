

#include "Dijkstra.h"
#include <queue>
#include <limits>
#include <chrono>
#include <algorithm>

PathResult Dijkstra::shortestPath(const Graph& g, long long src, long long dst) {
    PathResult result;
    result.found = false;
    result.totalDistance = std::numeric_limits<double>::infinity();
    result.visitedNodes = 0;

    if (!g.hasNode(src) || !g.hasNode(dst)) {
        return result;
    }


    std::unordered_map<long long, double> dist;

    std::unordered_map<long long, long long> prev;

    for (const auto& kv : g.nodes) {
        dist[kv.first] = std::numeric_limits<double>::infinity();
    }
    dist[src] = 0.0;

