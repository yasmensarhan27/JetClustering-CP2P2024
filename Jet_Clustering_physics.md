# Jet Clustering
## What Are Jets? [1](https://cms.cern/news/jets-cms-and-determination-their-energy-scale)
"jets" refer to collimated hadrons produced during strong high-energy particle interactions, particularly in experiments conducted at particle accelerators. 
The partons (eg. produced quarks and gluons) hadronize creating hadrons which are collimated together creating the ”Jets”

##What is Jet Clustering?
 Jet clustering is a computational process used in particle physics to identify and analyze jets.
<img width="471" alt="image" src="https://github.com/ubsuny/JetClustering-CP2P2024/assets/38404107/48d7b95e-a251-4bd0-bfbd-077baad1716d">
Fig.(1)[Jets are the experimental signatures of quarks and gluons produced in high-energy processes such as head-on proton-proton collisions](https://github.com/ubsuny/JetClustering-CP2P2024/assets/38404107/8cf340c3-6493-4ee5-a527-a5af587ca0d2)
][1](https://cms.cern/news/jets-cms-and-determination-their-energy-scale)

## Why Jet Clustering?
 Individual hadrons within a jet can not to be directly resolved by detectors.
Grouping Particles:  reconstruct these jets by grouping the final state particles based on their properties, typically their momenta (energies and directions).
Further analysis can be done on the reconstructed jets.

<img width="414" alt="image" src="https://github.com/ubsuny/JetClustering-CP2P2024/assets/38404107/99bbd06f-edb4-49c8-88cd-0d57a1c84892">
Fig.(2)[3][Double Higgs production at CMS](https://www.researchgate.net/publication/362844439_Double_Higgs_production_at_CMS)

## Jet clustering algorithms
Sequential Recombination Algorithms: 
It starts with the final state particles, merges the closest pair of jets into a pseudo-jet until a certain condition is met (e.g. Energy threshold, max no. of jets). Example: Kt- Algorithm, Anti-kt Algorithm, ..etc.
K-means Algorithm: Less common in jet clustering, but can be used in specific cases.

##Fastjet:
it is a C++ library used for jet finding in high-energy physics analyses.
It provides efficient and robust algorithms for jet clustering.

## Popular Jet clustering algorithms:
### Kt-Algorithm: 
𝒅_𝒊𝒋=𝒎𝒊𝒏(𝒑_𝒕𝒊^𝟐, 𝒑_𝒕𝒋^𝟐 )  (𝚫𝐑_𝐢𝐣^𝟐)/𝐑^𝟐 𝑑_𝑖𝑗 is the distance between jets i and j.
𝑝_𝑡𝑖  and 𝑝_𝑡𝑗 and are the momenta (energies and directions) of jets i and j, respectively.
Δij is the standard distance metric used for comparing jets, often Euclidean distance based on momenta.






References:

1- [JETS AT CMS AND THE DETERMINATION OF THEIR ENERGY SCALE](https://cms.cern/news/jets-cms-and-determination-their-energy-scale)

2- [anti-kt algorithm](https://arxiv.org/abs/0802.1189)

3- [Double Higgs production at CMS](https://www.researchgate.net/publication/362844439_Double_Higgs_production_at_CMS)
