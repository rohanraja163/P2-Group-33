//
// Created by adits on 3/28/2026.
//

#ifndef P2_GROUP_33_DIJKSTRA_H
#define P2_GROUP_33_DIJKSTRA_H

#include "Graph.h"
#include <vector>
#include <unordered_map>

struct PathResult {
    std::vector<long long> path;
    double totalDistance;
    long long visitedNodes;
    double executionTimeMs;
    bool found;
};

class Dijkstra {
public:

    PathResult shortestPath(const Graph& g, long long src, long long dst);
};



#endif //P2_GROUP_33_DIJKSTRA_H