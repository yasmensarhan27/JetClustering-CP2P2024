#pragma once

#include <vector>

struct Particle {
    double energy;
    double px, py, pz;
};

class JetClustering {
public:
    std::vector<Particle> kt_algorithm(const std::vector<Particle>& particles);
    // Add other clustering algorithms and methods as needed
};
