import numpy as np
import time

class Particle:
    def __init__(self, px, py, pz, E):
        self.px = px
        self.py = py
        self.pz = pz
        self.E = E
        self.pt = np.sqrt(px**2 + py**2)
        self.phi = np.arctan2(py, px)

def delta_R(particle1, particle2):
    deta = particle1.py - particle2.py
    dphi = np.abs(particle1.phi - particle2.phi)
    if dphi > np.pi:
        dphi = 2 * np.pi - dphi
    return np.sqrt(deta**2 + dphi**2)

def run_anti_kt(particles, R):
    start_time = time.time()
    jets = []
    while len(particles) > 0:
        min_distance = float('inf')
        min_i = -1
        min_j = -1
        for i in range(len(particles)):
            for j in range(i+1, len(particles)):
                d_ij = delta_R(particles[i], particles[j])
                if d_ij < min_distance:
                    min_distance = d_ij
                    min_i = i
                    min_j = j
        if min_distance > R:
            # No particles within distance R, so create a single-particle jet
            jets.append([particles[min_i]])
            del particles[min_i]
        else:
            # Merge particles and append them to a jet list
            merged_jet = [particles[min_i], particles[min_j]]
            jets.append(merged_jet)
            del particles[min_i]  # Delete the first merged particle
            # Delete the second merged particle by shifting remaining elements
            del particles[min_j - 1]
    end_time = time.time()
    runtime = end_time - start_time
    return jets, runtime

# Define particles
particles = [
    Particle(px=99, py=0.1, pz=0, E=100),
    Particle(px=4, py=-0.1, pz=0, E=5),
    Particle(px=-99, py=0, pz=0, E=99)
]

# Set clustering parameter
R = 0.7

# Run anti-kt algorithm
jets, runtime = run_anti_kt(particles.copy(), R)  # Avoid modifying original list

# Print the jets with constituent particles
print("Clustered with Longitudinally invariant anti-kt algorithm with R =", R)
print("        pt y phi")
for i, jet in enumerate(jets):
    print(f"jet {i}: {sum(p.pt for p in jet)} {jet[0].py} {jet[0].phi}")  # Assuming first particle has y & phi
    for i_constituent, constituent in enumerate(jet):
        print(f"    constituent {i_constituent}'s pt: {constituent.pt}")

# Print runtime
print(f"Runtime: {runtime} seconds")