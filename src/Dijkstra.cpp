

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

    using PQEntry = std::pair<double, long long>;
    std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<PQEntry>> pq;
    pq.push({0.0, src});

    auto startTime = std::chrono::high_resolution_clock::now();

    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();


        if (cost > dist[u]) continue;

        result.visitedNodes++;

        if (u == dst) {
            result.found = true;
            result.totalDistance = cost;
            break;
        }

        auto it = g.adjList.find(u);
        if (it == g.adjList.end()) continue;

        for (const Edge& e : it->second) {
            double newDist = dist[u] + e.distance;
            if (newDist < dist[e.to]) {
                dist[e.to] = newDist;
                prev[e.to] = u;
                pq.push({newDist, e.to});
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