#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"

using namespace std;
using namespace fastjet;

vector<PseudoJet> generate_random_particles(int num_particles) {
    vector<PseudoJet> particles;
    for (int i = 0; i < num_particles; ++i) {
        // Generate random momentum and energy values
        double pt = rand() % 100 + 1;
        double eta = -1 + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 2));
        double phi = 2 * M_PI * static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        double energy = rand() % 100 + 1;
        particles.push_back(PseudoJet(pt, eta, phi, energy));
    }
    return particles;
}

double run_jet_clustering(int num_particles) {
    // Generate random particles
    vector<PseudoJet> particles = generate_random_particles(num_particles);

    // Record start time
    clock_t start_time = clock();

    // Choose a jet definition
    double R = 0.7;
    JetDefinition jet_def(antikt_algorithm, R);

    // Run clustering, extract jets
    ClusterSequence cs(particles, jet_def);
    vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

    // Record end time
    clock_t end_time = clock();

    // Calculate runtime
    double runtime = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Print out some info
    cout << "Fast Version - Clustered with " << jet_def.description() << endl;

    // Print the jets
    cout << "        pt y phi" << endl;
    for (size_t i = 0; i < jets.size(); ++i) {
        cout << "jet " << i << ": " << jets[i].pt() << " " << jets[i].rap() << " " << jets[i].phi() << endl;
        vector<PseudoJet> constituents = jets[i].constituents();
        for (size_t j = 0; j < constituents.size(); ++j) {
            cout << "    constituent " << j << "'s pt: " << constituents[j].pt() << endl;
        }
    }

    // Return runtime
    return runtime;
}

double run_slow_jet_clustering(int num_particles) {
    // Generate random particles
    vector<PseudoJet> particles = generate_random_particles(num_particles);

    // Record start time
    clock_t start_time = clock();

    // Choose a jet definition
    double R = 0.7;
    JetDefinition jet_def(antikt_algorithm, R);

    // Loop to simulate slow clustering
    for (int k = 0; k < 1000; ++k) {
        // Run clustering, extract jets
        ClusterSequence cs(particles, jet_def);
        vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());
        // Print constituents
        for (size_t i = 0; i < jets.size(); ++i) {
            vector<PseudoJet> constituents = jets[i].constituents();
            for (size_t j = 0; j < constituents.size(); ++j) {
                double pt = constituents[j].pt(); // Ensure all constituents are calculated
            }
        }
    }

    // Record end time
    clock_t end_time = clock();

    // Calculate runtime
    double runtime = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Print out some info
    cout << "Slow Version - Clustered with " << jet_def.description() << endl;

    // Print the jets
    cout << "        pt y phi" << endl;
    ClusterSequence cs(particles, jet_def);
    vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());
    for (size_t i = 0; i < jets.size(); ++i) {
        cout << "jet " << i << ": " << jets[i].pt() << " " << jets[i].rap() << " " << jets[i].phi() << endl;
        vector<PseudoJet> constituents = jets[i].constituents();
        for (size_t j = 0; j < constituents.size(); ++j) {
            cout << "    constituent " << j << "'s pt: " << constituents[j].pt() << endl;
        }
    }

    // Return runtime
    return runtime;
}

int main() {
    int num_particles = 10; // Set the number of particles
    
    // Call the functions and print the runtimes
    double fast_runtime = run_jet_clustering(num_particles);
    double slow_runtime = run_slow_jet_clustering(num_particles);
    
    cout << "Fast Runtime: " << fast_runtime << " seconds" << endl;
    cout << "Slow Runtime: " << slow_runtime << " seconds" << endl;
    
    // Calculate the difference in runtimes
    double comparison = slow_runtime / fast_runtime;
    cout << "short version is: " << comparison << " longer" << endl;

    return 0;
}
