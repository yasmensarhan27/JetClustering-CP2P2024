#include <iostream>
#include <vector>
#include <cmath>

// Include the matplotlibcpp library for visualization
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

// Define a simple structure to represent particles
struct Particle {
    double x, y;
    // Add any other relevant information about the particle
};

// Function to calculate the Euclidean distance between two particles
double EuclideanDistance(const Particle& p1, const Particle& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

// Function to find the pair of particles with the minimum distance
std::pair<int, int> FindMinDistPair(const std::vector<Particle>& P) {
    double min_distance = std::numeric_limits<double>::infinity();
    std::pair<int, int> min_pair;

    for (int i = 0; i < P.size(); ++i) {
        for (int j = i + 1; j < P.size(); ++j) {
            double dist = EuclideanDistance(P[i], P[j]);
            if (dist < min_distance) {
                min_distance = dist;
                min_pair = std::make_pair(i, j);
            }
        }
    }

    return min_pair;
}

// Function to combine two particles into a single pseudo-particle by averaging
Particle CombineParticles(const Particle& p1, const Particle& p2) {
    Particle combined_particle;
    combined_particle.x = (p1.x + p2.x) / 2.0;
    combined_particle.y = (p1.y + p2.y) / 2.0;
    return combined_particle;
}

// Main kT jet finding algorithm
std::vector<Particle> KTJetFinding(std::vector<Particle>& P) {
    while (P.size() > 1) {
        auto [i, j] = FindMinDistPair(P);
        Particle combined_particle = CombineParticles(P[i], P[j]);
        P.erase(P.begin() + j);
        P[i] = combined_particle;
    }

    // The final remaining particle(s) represent the jets
    return P;
}

// Function to visualize particles using Matplotlib
void VisualizeParticles(const std::vector<Particle>& P) {
    // Extract x and y coordinates for plotting
    std::vector<double> x_coords, y_coords;
    for (const auto& particle : P) {
        x_coords.push_back(particle.x);
        y_coords.push_back(particle.y);
    }

    // Plot the particles
    plt::scatter(x_coords, y_coords);
    plt::title("Visualization of Particles");
    plt::xlabel("X Coordinate");
    plt::ylabel("Y Coordinate");
    plt::show();
}

int main() {
    // Example usage:
    std::vector<Particle> particles = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
    std::vector<Particle> jets = KTJetFinding(particles);

    // Display the resulting jets
    for (const auto& jet : jets) {
        std::cout << "Jet: (" << jet.x << ", " << jet.y << ")\n";
    }

    // Visualize the particles
    VisualizeParticles(particles);

    return 0;
}
