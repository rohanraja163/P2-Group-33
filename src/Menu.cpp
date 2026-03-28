//
// Created by Kavya Patel on 3/28/26.
//
#include "Menu.h"
#include "DataLoader.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>

void Menu::printSeparator() const {
    std::cout << std::string(60, '=') << "\n";
}

void Menu::printHeader() const {
    printSeparator();
    std::cout << "   Efficient Pathfinding in Large Transportation Networks\n";
    printSeparator();
}

void Menu::run() {
    printHeader();

    int choice = 0;
    while (true) {
        std::cout << "\nMAIN MENU\n";
        std::cout << "  [1] Load dataset\n";
        std::cout << "  [2] Select start and destination nodes\n";
        std::cout << "  [3] Run Dijkstra's Algorithm\n";
        std::cout << "  [4] Run A* Algorithm\n";
        std::cout << "  [5] Compare both algorithms\n";
        std::cout << "  [6] Exit\n";
        std::cout << "Enter choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[Error] Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: loadDataset();        break;
            case 2: selectNodes();        break;
            case 3: runDijkstra();        break;
            case 4: runAStar();           break;
            case 5: compareAlgorithms();  break;
            case 6:
                std::cout << "Goodbye!\n";
                return;
            default:
                std::cout << "[Error] Invalid choice. Please select 1-6.\n";
        }
    }
}

void Menu::loadDataset() {
    std::cout << "\nLOAD DATASET\n";
    std::cout << "  [1] Load from CSV file\n";
    std::cout << "  [2] Generate synthetic dataset (100,000 nodes)\n";
    std::cout << "  [3] Generate small test dataset (1,000 nodes)\n";
    std::cout << "Enter choice: ";

    int sub;
    if (!(std::cin >> sub)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    DataLoader loader;
    graph = Graph(); 

    if (sub == 1) {
        std::cout << "Enter filepath: ";
        std::string path;
        std::cin >> path;
        datasetLoaded = loader.loadFromFile(path, graph);
    } else if (sub == 2 || sub == 3) {
        int numNodes = (sub == 2) ? 100000 : 1000;
        std::string filepath = (sub == 2) ? "data/network_100k.csv" : "data/network_1k.csv";
        
        system("mkdir -p data");
        if (loader.generateSyntheticDataset(filepath, numNodes)) {
            datasetLoaded = loader.loadFromFile(filepath, graph);
        }
    } else {
        std::cout << "[Error] Invalid choice.\n";
        return;
    }

    if (datasetLoaded) {
        std::cout << "[Info] Graph ready: " << graph.nodeCount() << " nodes, "
                  << graph.edgeCount() / 2 << " undirected edges.\n";
        startNode = -1;
        destNode  = -1;
    } else {
        std::cout << "[Error] Failed to load dataset.\n";
    }
}

void Menu::selectNodes() {
    if (!datasetLoaded) {
        std::cout << "[Error] Please load a dataset first.\n";
        return;
    }

    std::cout << "\nSELECT NODES\n";
    std::cout << "Valid node IDs range: check your dataset.\n";
    std::cout << "Enter start node ID: ";
    long long s;
    if (!(std::cin >> s)) {
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[Error] Invalid input.\n"; return;
    }
    std::cout << "Enter destination node ID: ";
    long long d;
    if (!(std::cin >> d)) {
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[Error] Invalid input.\n"; return;
    }

    if (!graph.hasNode(s)) {
        std::cout << "[Error] Node " << s << " does not exist in the graph.\n"; return;
    }
    if (!graph.hasNode(d)) {
        std::cout << "[Error] Node " << d << " does not exist in the graph.\n"; return;
    }

    startNode = s;
    destNode  = d;
    std::cout << "[Info] Start: " << startNode << "  Destination: " << destNode << "\n";
}
