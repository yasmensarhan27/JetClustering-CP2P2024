#pragma once

#include <vector>
#include <fastjet/PseudoJet.hh>

class KtAlgorithm {
public:
    std::vector<fastjet::PseudoJet> run(const std::vector<fastjet::PseudoJet>& inputParticles);
};
