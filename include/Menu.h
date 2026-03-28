#ifndef MENU_H
#define MENU_H

#include "Graph.h"
#include "Dijkstra.h"
#include "AStar_real.h"

class Menu_real {
public:
    void run();

private:
    Graph graph;
    long long startNode = -1;
    long long destNode  = -1;
    bool datasetLoaded  = false;

    
};

#endif