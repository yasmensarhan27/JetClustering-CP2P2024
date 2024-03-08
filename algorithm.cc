#include "algorithms.h"
#include <limits>
#include <cmath>

double distance(const fastjet::PseudoJet& p1, const fastjet::PseudoJet& p2) {
    return std::sqrt(std::pow(p1.eta() - p2.eta(), 2) + std::pow(p1.phi() - p2.phi(), 2));
}

std::pair<int, int> findClosestParticles(const std::vector<fastjet::PseudoJet>& particles) {
    int closestI = -1, closestJ = -1;
    double minDistance = std::numeric_limits<double>::max();

    for (int i = 0; i < particles.size(); ++i) {
        for (int j = i + 1; j < particles.size(); ++j) {
            double dist = distance(particles[i], particles[j]);
            if (dist < minDistance) {
                minDistance = dist;
                closestI = i;
                closestJ = j;
            }
        }
    }

    return {closestI, closestJ};
}

fastjet::PseudoJet mergeParticles(const fastjet::PseudoJet& p1, const fastjet::PseudoJet& p2) {
    // In a simple version, you can merge by adding their four-momenta
    return p1 + p2;
}

std::vector<fastjet::PseudoJet> KtAlgorithm::run(const std::vector<fastjet::PseudoJet>& inputParticles) {
    // Simplified kT algorithm
    std::vector<fastjet::PseudoJet> clusters = inputParticles;

    while (clusters.size() > 1) {
        // Find the pair of particles with the smallest distance
        auto [i, j] = findClosestParticles(clusters);

        // Merge the closest particles
        fastjet::PseudoJet mergedParticle = mergeParticles(clusters[i], clusters[j]);

        // Remove the original particles from the list
        clusters.erase(clusters.begin() + j);
        clusters.erase(clusters.begin() + i);

        // Add the merged particle to the list
        clusters.push_back(mergedParticle);
    }

    return clusters;
}
