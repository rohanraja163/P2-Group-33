#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

bool DataLoader::loadFromFile(const std::string& filepath, Graph& graph) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "[Error] Cannot open file: " << filepath << "\n";
        return false;
    }

    std::string line;
    long long nodesLoaded = 0, edgesLoaded = 0;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; 

        std::istringstream ss(line);
        std::string type;
        std::getline(ss, type, ',');

        if (type == "node") {
            std::string idStr, latStr, lonStr;
            std::getline(ss, idStr, ',');
            std::getline(ss, latStr, ',');
            std::getline(ss, lonStr, ',');
            try {
                long long id  = std::stoll(idStr);
                double lat    = std::stod(latStr);
                double lon    = std::stod(lonStr);
                graph.addNode(id, lat, lon);
                nodesLoaded++;
            } catch (...) {
                
            }
        } else if (type == "edge") {
            std::string fromStr, toStr, distStr;
            std::getline(ss, fromStr, ',');
            std::getline(ss, toStr,   ',');
            std::getline(ss, distStr, ',');
            try {
                long long from = std::stoll(fromStr);
                long long to   = std::stoll(toStr);
                double dist    = std::stod(distStr);
                graph.addEdge(from, to, dist);
                edgesLoaded++;
            } catch (...) {
                
            }
        }
    }
    file.close();
    std::cout << "[Info] Loaded " << nodesLoaded << " nodes and "
              << edgesLoaded << " edges.\n";
    return (nodesLoaded > 0);
}
