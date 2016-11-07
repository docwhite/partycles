#include <iostream>
#include "particlesystem.h"

#include <thrust/fill.h>
#include <thrust/random.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>

void modifying_vbo(unsigned int VBO_id, ParticleSystem* ps);

ParticleSystem::ParticleSystem()
{
    numParts = 0;
}

void ParticleSystem::birth_particle()
{
    positions.push_back(0.0f);
    positions.push_back(0.5f);
    positions.push_back(0.0f);
    velocities.push_back(0.01f *  (2*((float)rand()/RAND_MAX)-1));
    velocities.push_back(0.01f *  (2*((float)rand()/RAND_MAX)-1));
    velocities.push_back(0.01f *  (2*((float)rand()/RAND_MAX)-1));

    numParts += 1;
}

void ParticleSystem::advance_particles(unsigned int VBO_id)
{
    modifying_vbo(VBO_id, this);
}

struct prg
{
    float a, b;

    __host__ __device__
    prg(float _a=0.0f, float _b=1.0f) : a(_a), b(_b) {};

    __host__ __device__
        float operator()(const unsigned int n) const
        {
            thrust::default_random_engine rng;
            thrust::uniform_real_distribution<float> dist(a, b);
            rng.discard(n);

            return dist(rng);
        }
};

void ParticleSystem::initialize_system(int _numParts)
{
    numParts = _numParts;
    positions = thrust::device_vector<float>(3 * numParts);
    velocities = thrust::device_vector<float>(3 * numParts);
    thrust::fill(positions.begin(), positions.end(), 0.0f);

    thrust::counting_iterator<unsigned int> index_sequence_begin(0);

    thrust::transform(index_sequence_begin,
                      index_sequence_begin + 3*numParts,
                      velocities.begin(),
                      prg(-0.01f,0.01f));

}
