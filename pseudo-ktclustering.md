$$
Data: Particle(pt, eta, phi)

Function: distance(particle1, particle2)
   Calculates Euclidean distance in eta-phi plane
   Returns distance

 Function: find_closest_particles(particles)
   Initialize min_distance = infinity, closest_i = -1, closest_j = -1
   FOR each particle i in particles
     FOR each particle j in particles (j > i) // Avoid duplicates
       Calculate distance between particles[i] and particles[j]
       IF distance < min_distance
         Update min_distance, closest_i, closest_j
   RETURN (closest_i, closest_j)

 Function: merge_particles(particle1, particle2)
   Combine pt, eta, phi using a specific merging strategy (simple addition here)
   Returns a new Particle object with merged properties

 Function: kt_clustering(particles)
   Initialize jets = copy of particles
   WHILE size of jets > 1
     (closest_i, closest_j) = find_closest_particles(jets)
     merged_particle = merge_particles(jets[closest_i], jets[closest_j])
     Remove jets[closest_i] and jets[closest_j] from jets (maintain order)
     Add merged_particle to jets
   RETURN jets

// Main program
particles = { /* List of particle properties */ }

jets = kt_clustering(particles)

print properties of jets[0] (final clustered particle)
$$
