import time
import random
import numpy as np
import tensorflow as tf
import fastjet as fj

def generate_random_particles(num_particles):
    pt = np.random.uniform(low=0, high=100, size=num_particles)
    eta = np.random.uniform(low=-1, high=1, size=num_particles)
    phi = np.random.uniform(low=0, high=2 * np.pi, size=num_particles)
    particles = np.stack([pt, eta, phi], axis=1)
    return particles

def run_jet_clustering_tf(num_particles):
    # Generate random particles
    particles = generate_random_particles(num_particles)

    # Initialize lists to store jets and their constituents
    jets = []
    constituents = []

    # Loop over particles
    while particles.shape[0] > 0:
        # Select a seed particle randomly
        seed_index = random.randint(0, particles.shape[0] - 1)
        seed = particles[seed_index]

        # Identify nearby particles
        distances = delta_r(seed[1], seed[2], particles[:, 1], particles[:, 2])
        nearby_indices = np.where(distances < 0.7)[0]

        # Combine nearby particles into a cluster
        cluster = np.sum(particles[nearby_indices], axis=0)
        jets.append(cluster)

        # Save constituents of the cluster
        constituents.append(particles[nearby_indices])

        # Remove clustered particles
        particles = np.delete(particles, nearby_indices, axis=0)

    return jets, constituents

def delta_r(eta1, phi1, eta2, phi2):
    deta = eta1 - eta2
    dphi = np.abs(phi1 - phi2)
    dphi = np.minimum(dphi, 2 * np.pi - dphi)
    return np.sqrt(deta**2 + dphi**2)

def print_jets_tf(jets, constituents):
    print("        pt y phi")
    for i, jet in enumerate(jets):
        pt = jet[0]
        y = jet[1]
        phi = jet[2]
        print(f"jet {i}: {pt} {y} {phi}")
        for j, constituent in enumerate(constituents[i]):
            print(f"    constituent {j}'s pt: {constituent[0]}")

def run_jet_clustering_fj(num_particles):
    # Generate random particles
    particles = generate_random_particles(num_particles)

    # Convert to FastJet format
    fj_particles = [fj.PseudoJet(pt, eta, phi, 0) for pt, eta, phi in particles]

    # Perform jet clustering with FastJet
    jet_def = fj.JetDefinition(fj.antikt_algorithm, 0.7)
    cs = fj.ClusterSequence(fj_particles, jet_def)
    jets_fj = fj.sorted_by_pt(cs.inclusive_jets())

    # Store constituent information before it goes out of scope
    fj_constituents = [jet.constituents() for jet in jets_fj]

    return jets_fj, fj_constituents

def print_jets_fj(jets_fj, fj_constituents):
    print("        pt y phi")
    for i, jet in enumerate(jets_fj):
        pt = jet.pt()
        y = jet.rap()
        phi = jet.phi()
        print(f"jet {i}: {pt} {y} {phi}")
        constituents = fj_constituents[i]
        for j, constituent in enumerate(constituents):
            print(f"    constituent {j}'s pt: {constituent.pt()}")

num_particles = 10  # Set the number of particles

# TensorFlow Version
start_time = time.time()
tf_jets, tf_constituents = run_jet_clustering_tf(num_particles)
end_time_tf = time.time()

# FastJet Version
start_time_fj = time.time()
jets_fj, fj_constituents = run_jet_clustering_fj(num_particles)
end_time_fj = time.time()

# Print out results and comparison
print("TensorFlow Version - Clustered")
print_jets_tf(tf_jets, tf_constituents)
print("TensorFlow Runtime:", end_time_tf - start_time, "seconds")

print("\nFastJet Version - Clustered")
print_jets_fj(jets_fj, fj_constituents)
print("FastJet Runtime:", end_time_fj - start_time_fj, "seconds")
