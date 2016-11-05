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
