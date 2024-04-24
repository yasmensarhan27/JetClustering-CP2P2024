import time
import fastjet as fj

def run_jet_clustering():
    # Define particles
    particles = [fj.PseudoJet(99.0, 0.1, 0, 100.0),
                 fj.PseudoJet(4.0, -0.1, 0, 5.0),
                 fj.PseudoJet(-99.0, 0, 0, 99.0)]
    # Record start time
    start_time = time.time()

    # Choose a jet definition
    R = 0.7
    jet_def = fj.JetDefinition(fj.antikt_algorithm, R)



    # Run clustering, extract jets
    cs = fj.ClusterSequence(particles, jet_def)
    jets = sorted(cs.inclusive_jets(), key=lambda jet: -jet.pt())

    # Record end time
    end_time = time.time()

    # Calculate runtime
    runtime = end_time - start_time

    # Print out some info
    print("Clustered with", jet_def.description())

    # Print the jets
    print("        pt y phi")
    for i, jet in enumerate(jets):
        print(f"jet {i}: {jet.pt()} {jet.rap()} {jet.phi()}")
        constituents = jet.constituents()
        for j, constituent in enumerate(constituents):
            print(f"    constituent {j}'s pt: {constituent.pt()}")

    # Return runtime
    return runtime

# Call the function and print the runtime
runtime = run_jet_clustering()
print(f"Runtime: {runtime} seconds")

