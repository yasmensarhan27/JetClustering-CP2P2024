#include "visualization.h"
#include "TCanvas.h"
#include "TH1F.h"

void Visualization::visualize(const std::vector<fastjet::PseudoJet>& jets) {
    TCanvas* canvas = new TCanvas("canvas", "Jet Clustering Visualization", 800, 600);

    // Define histograms
    TH1F* ptHistogram = new TH1F("ptHistogram", "Jet Transverse Momentum Distribution", 100, 0, 1000);

    // Fill histograms with jet information
    for (const auto& jet : jets) {
        ptHistogram->Fill(jet.pt());
    }

    // Draw histograms
    ptHistogram->Draw();
    canvas->Update();

    // Save visualization
    canvas->SaveAs("jet_clustering_visualization.root");
}
