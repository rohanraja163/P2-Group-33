#ifndef MENU_H
#define MENU_H

#include "Graph.h"
#include "Dijkstra.h"
#include "AStar.h"

class Menu {
public:
    void run();

private:
    Graph graph;
    long long startNode = -1;
    long long destNode  = -1;
    bool datasetLoaded  = false;

    
    void loadDataset();
    void selectNodes();
    void runDijkstra();
    void runAStar();
    void compareAlgorithms();
    void displayPath(const PathResult& result, const std::string& algorithmName);
    void printHeader() const;
    void printSeparator() const;
};

#endif
