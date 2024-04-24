import time
import random
import fastjet as fj

def generate_random_particles(num_particles):
    particles = []
    for _ in range(num_particles):
        # Generate random momentum and energy values
        pt = random.uniform(0, 100)
        eta = random.uniform(-1, 1)
        phi = random.uniform(0, 2 * fj.pi)
        energy = random.uniform(0, 100)
        particles.append(fj.PseudoJet(pt, eta, phi, energy))
    return particles

def run_jet_clustering(num_particles):
    # Generate random particles
    particles = generate_random_particles(num_particles)

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
    print("Fast Version - Clustered with", jet_def.description())

    # Print the jets
    print("        pt y phi")
    for i, jet in enumerate(jets):
        print(f"jet {i}: {jet.pt()} {jet.rap()} {jet.phi()}")
        constituents = jet.constituents()
        for j, constituent in enumerate(constituents):
            print(f"    constituent {j}'s pt: {constituent.pt()}")

    # Return runtime
    return runtime

def run_slow_jet_clustering(num_particles):
    # Generate random particles
    particles = generate_random_particles(num_particles)

    # Record start time
    start_time = time.time()

    # Choose a jet definition
    R = 0.7
    jet_def = fj.JetDefinition(fj.antikt_algorithm, R)

    # Loop to simulate slow clustering
    for _ in range(1000):
        # Run clustering, extract jets
        cs = fj.ClusterSequence(particles, jet_def)
        jets = sorted(cs.inclusive_jets(), key=lambda jet: -jet.pt())
        # Print constituents
        for jet in jets:
            constituents = jet.constituents()
            for j, constituent in enumerate(constituents):
                _ = constituent.pt()  # To ensure all constituents are calculated, but not printing here

    # Record end time
    end_time = time.time()

    # Calculate runtime
    runtime = end_time - start_time

    # Print out some info
    print("Slow Version - Clustered with", jet_def.description())

    # Print the jets
    print("        pt y phi")
    for i, jet in enumerate(jets):
        print(f"jet {i}: {jet.pt()} {jet.rap()} {jet.phi()}")
        constituents = jet.constituents()
        for j, constituent in enumerate(constituents):
            print(f"    constituent {j}'s pt: {constituent.pt()}")

    # Return runtime
    return runtime

num_particles = 10  # Set the number of particles
# Call the functions and print the runtimes
fast_runtime = run_jet_clustering(num_particles)
slow_runtime = run_slow_jet_clustering(num_particles)

print(f"Fast Runtime: {fast_runtime} seconds")
print(f"Slow Runtime: {slow_runtime} seconds")

# Calculate the difference in runtimes
comparison = slow_runtime / fast_runtime
print(f"slow version is : {comparison} times longer than the fast version")
