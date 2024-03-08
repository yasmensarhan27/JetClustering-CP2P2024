#pragma once

#include <vector>
#include <fastjet/PseudoJet.hh>

class Visualization {
public:
    void visualize(const std::vector<fastjet::PseudoJet>& jets);
};
