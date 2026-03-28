#ifndef DATALOADER_H
#define DATALOADER_H

#include "Graph.h"
#include <string>

class DataLoader {
public:
    
    
    
    
    
    bool loadFromFile(const std::string& filepath, Graph& graph);

    
    
    bool generateSyntheticDataset(const std::string& filepath, int numNodes);
};

#endif
