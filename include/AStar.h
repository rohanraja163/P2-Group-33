#ifndef ASTAR_H
#define ASTAR_H

#include "Graph.h"
#include "Dijkstra.h"   

class AStar_real {
public:
    
    PathResult shortestPath(const Graph& g, long long src, long long dst);

private:
    
    double heuristic(const Node& a, const Node& b) const;
};

#endif
