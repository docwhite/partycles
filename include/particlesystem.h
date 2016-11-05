#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include "particle.h"

class ParticleSystem
{
public:
    ParticleSystem();
    void birth_particle();
    std::vector<Particle> m_particles;
};

#endif // PARTICLESYSTEM_H
