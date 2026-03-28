
#include "AStar.h"
#include <queue>
#include <limits>
#include <chrono>
#include <algorithm>
#include <cmath>

double AStar_real::heuristic(const Node& a, const Node& b) const {
    const double R = 6371.0;
    double dLat = (b.latitude  - a.latitude)  * M_PI / 180.0;
    double dLon = (b.longitude - a.longitude) * M_PI / 180.0;
    double lat1 = a.latitude * M_PI / 180.0;
    double lat2 = b.latitude * M_PI / 180.0;

    double aVal = std::sin(dLat / 2) * std::sin(dLat / 2)
                + std::cos(lat1) * std::cos(lat2)
                * std::sin(dLon / 2) * std::sin(dLon / 2);
    double c = 2.0 * std::atan2(std::sqrt(aVal), std::sqrt(1.0 - aVal));
    return R * c;
}


PathResult AStar_real::shortestPath(const Graph& g, long long src, long long dst) {
    PathResult result;
    result.found         = false;
    result.totalDistance = std::numeric_limits<double>::infinity();
    result.visitedNodes  = 0;

    if (!g.hasNode(src) || !g.hasNode(dst)) {
        return result;
    }

    const Node& dstNode = g.nodes.at(dst);


    std::unordered_map<long long, double> gScore;

    std::unordered_map<long long, double> fScore;
    std::unordered_map<long long, long long> prev;

    for (const auto& kv : g.nodes) {
        gScore[kv.first] = std::numeric_limits<double>::infinity();
        fScore[kv.first] = std::numeric_limits<double>::infinity();
    }
    gScore[src] = 0.0;
    fScore[src] = heuristic(g.nodes.at(src), dstNode);


    using PQEntry = std::pair<double, long long>;
    std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<PQEntry>> openSet;
    openSet.push({fScore[src], src});

    auto startTime = std::chrono::high_resolution_clock::now();

    while (!openSet.empty()) {
        auto [f, u] = openSet.top();
        openSet.pop();


        if (f > fScore[u]) continue;

        result.visitedNodes++;

        if (u == dst) {
            result.found         = true;
            result.totalDistance = gScore[dst];
            break;
        }

        auto it = g.adjList.find(u);
        if (it == g.adjList.end()) continue;

        for (const Edge& e : it->second) {
            double tentative = gScore[u] + e.distance;
            if (tentative < gScore[e.to]) {
                prev[e.to]    = u;
                gScore[e.to]  = tentative;
                fScore[e.to]  = tentative + heuristic(g.nodes.at(e.to), dstNode);
                openSet.push({fScore[e.to], e.to});
            }
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    result.executionTimeMs =
        std::chrono::duration<double, std::milli>(endTime - startTime).count();


    if (result.found) {
        long long cur = dst;
        while (cur != src) {
            result.path.push_back(cur);
            auto pit = prev.find(cur);
            if (pit == prev.end()) { result.found = false; break; }
            cur = pit->second;
        }
        result.path.push_back(src);
        std::reverse(result.path.begin(), result.path.end());
    }

    return result;
}
