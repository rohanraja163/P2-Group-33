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

bool DataLoader::generateSyntheticDataset(const std::string& filepath, int numNodes) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "[Error] Cannot create file: " << filepath << "\n";
        return false;
    }

    std::cout << "[Info] Generating synthetic dataset with " << numNodes << " nodes...\n";

    
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> latDist(25.0, 49.0);   
    std::uniform_real_distribution<double> lonDist(-125.0, -67.0); 

    
    file << "# Synthetic road network dataset\n";
    file << "# Format: node,id,lat,lon  OR  edge,from,to,distance\n";

    
    std::vector<std::pair<double,double>> coords(numNodes);
    for (int i = 0; i < numNodes; i++) {
        double lat = latDist(rng);
        double lon = lonDist(rng);
        coords[i] = {lat, lon};
        file << "node," << i << "," << lat << "," << lon << "\n";
    }

    
    
    long long edgeCount = 0;
    int connectionsPerNode = 4;

    
    auto haversine = [](double lat1, double lon1, double lat2, double lon2) -> double {
        const double R = 6371.0;
        double dLat = (lat2 - lat1) * M_PI / 180.0;
        double dLon = (lon2 - lon1) * M_PI / 180.0;
        double a = std::sin(dLat/2)*std::sin(dLat/2)
                 + std::cos(lat1*M_PI/180.0) * std::cos(lat2*M_PI/180.0)
                 * std::sin(dLon/2)*std::sin(dLon/2);
        return R * 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0-a));
    };

    for (int i = 0; i < numNodes; i++) {
        
        for (int k = 1; k <= connectionsPerNode && (i + k) < numNodes; k++) {
            double dist = haversine(coords[i].first, coords[i].second,
                                    coords[i+k].first, coords[i+k].second);
            file << "edge," << i << "," << (i+k) << "," << dist << "\n";
            edgeCount++;
        }
        
        if (i + 100 < numNodes) {
            double dist = haversine(coords[i].first, coords[i].second,
                                    coords[i+100].first, coords[i+100].second);
            file << "edge," << i << "," << (i+100) << "," << dist << "\n";
            edgeCount++;
        }
        
        if (i % 2 == 0 && i + 51 < numNodes) {
            double dist = haversine(coords[i].first, coords[i].second,
                                    coords[i+51].first, coords[i+51].second);
            file << "edge," << i << "," << (i+51) << "," << dist << "\n";
            edgeCount++;
        }
    }
    file.close();
    std::cout << "[Info] Generated " << numNodes << " nodes and "
              << edgeCount << " edges -> " << filepath << "\n";
    return true;
}
