//
// Created by Kavya Patel on 3/28/26.
//

#include "AStar.h"
#include <queue>
#include <limits>
#include <chrono>
#include <algorithm>
#include <cmath>

double AStar_real::heuristic(const Node& a, const Node& b) const {
    const double R = 6371.0;
    double dLat = (b.latitude  - a.latitude)  * M_PI / 180.0;
    double dLon = (b.longitude - a.longitude) * M_PI / 180.0;
    double lat1 = a.latitude * M_PI / 180.0;
    double lat2 = b.latitude * M_PI / 180.0;

    double aVal = std::sin(dLat / 2) * std::sin(dLat / 2)
                + std::cos(lat1) * std::cos(lat2)
                * std::sin(dLon / 2) * std::sin(dLon / 2);
    double c = 2.0 * std::atan2(std::sqrt(aVal), std::sqrt(1.0 - aVal));
    return R * c;
}