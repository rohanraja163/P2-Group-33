#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <string>

struct Node {
    long long id;
    double latitude;
    double longitude;
};

struct Edge {
    long long to;
    double distance;
};
class Graph {
public:
    
    std::unordered_map<long long, Node> nodes;
    
    std::unordered_map<long long, std::vector<Edge>> adjList;

    
    void addNode(long long id, double lat, double lon);

    
    void addEdge(long long from, long long to, double distance);

    
    bool hasNode(long long id) const;

    
    size_t nodeCount() const;

    
    size_t edgeCount() const;
};

#endif
