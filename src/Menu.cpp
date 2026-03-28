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
