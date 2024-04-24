#include "fastjet/ClusterSequence.hh"
#include <chrono>
#include <iostream>

using namespace fastjet;
using namespace std;

int main () {
    vector<PseudoJet> particles;
    // An event with three particles: px
    particles.push_back( PseudoJet(   99.0,  0.1,  0, 100.0) );
    particles.push_back( PseudoJet(    4.0, -0.1,  0,   5.0) );
    particles.push_back( PseudoJet(  -99.0, 0, 0, 99.0));
    
    // Choose a jet definition
    double R = 0.7;
    JetDefinition jet_def(antikt_algorithm, R);
    
    // Record start time
    auto start_time = chrono::high_resolution_clock::now();
    
    // Run the clustering, extract the jets
    ClusterSequence cs(particles, jet_def);
    vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());
    
    // Record end time
    auto end_time = chrono::high_resolution_clock::now();
    
    // Calculate runtime
    chrono::duration<double> runtime = end_time - start_time;
    
    // Print out some info
    cout << "Clustered with " << jet_def.description() << endl;
    
    // Print the jets
    cout <<   "        pt y phi" << endl;
    for (unsigned i = 0; i < jets.size(); i++) {
        cout << "jet " << i << ": "<< jets[i].perp() << " "
        << jets[i].rap() << " " << jets[i].phi() << endl;
        
        vector<PseudoJet> constituents = jets[i].constituents();
        for (unsigned j = 0; j < constituents.size(); j++) {
            cout << "    constituent " << j << "’s pt: "<< constituents[j].perp() << endl;
        }
    }

    // Print runtime
    cout << "Runtime: " << runtime.count() << " seconds" << endl;
}

