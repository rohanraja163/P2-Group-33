#include "Graph.h"

void Graph::addNode(long long id, double lat, double lon) {
    nodes[id] = {id, lat, lon};
    
    if (adjList.find(id) == adjList.end()) {
        adjList[id] = {};
    }
}

void Graph::addEdge(long long from, long long to, double distance) {
    adjList[from].push_back({to, distance});
    adjList[to].push_back({from, distance}); 
}

bool Graph::hasNode(long long id) const {
    return nodes.find(id) != nodes.end();
}

size_t Graph::nodeCount() const {
    return nodes.size();
}

size_t Graph::edgeCount() const {
    size_t total = 0;
    for (const auto& kv : adjList) {
        total += kv.second.size();
    }
    return total; 
}
