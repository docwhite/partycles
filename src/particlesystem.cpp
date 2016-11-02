#include <iostream>

#include "particlesystem.h"
#include "particle.h"

ParticleSystem::ParticleSystem()
{


}

void ParticleSystem::birth_particle()
{
    m_particles.push_back(Particle());
}


void ParticleSystem::step()
{
    for(std::vector<Particle>::iterator it = m_particles.begin(); it != m_particles.end(); ++it) {
        it->step();
    }
}
