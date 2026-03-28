//
// Created by adits on 3/28/2026.
//

#include "Dijkstra.h"
#include <queue>
#include <limits>
#include <chrono>
#include <algorithm>

PathResult Dijkstra::shortestPath(const Graph& g, long long src, long long dst) {
    PathResult result;
    result.found         = false;
    result.totalDistance = std::numeric_limits<double>::infinity();
    result.visitedNodes  = 0;