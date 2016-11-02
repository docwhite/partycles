// CUDA-C includes
#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include <vector>

#include "particlesystem.h"
#include "particle.h"

//Adds two arrays
extern "C"
void ramon(ParticleSystem& _ps, float * _vertices);

__global__ void blanquer(Particle* _particles)
{
    int index = threadIdx.x;
    _particles[index].m_pos_x = 0.9f;
    _particles[index].m_pos_y = 0.5f;
    _particles[index].m_pos_z = 0.0f;
}

// Main cuda function
void ramon(ParticleSystem& _ps, float * _vertices) {
    int size_of_ps = _ps.m_particles.size();

    Particle res[size_of_ps];
    Particle* d_particles;

    cudaMalloc((void**)&d_particles, size_of_ps * sizeof(Particle));

    cudaMemcpy((void**)d_particles, (void**)&_ps.m_particles[0], size_of_ps*sizeof(Particle), cudaMemcpyHostToDevice);

    blanquer<<<1,size_of_ps>>>(d_particles);

    cudaMemcpy((void*)res, (void*)d_particles, size_of_ps*sizeof(Particle), cudaMemcpyDeviceToHost);

    for( int i = 0 ; i < size_of_ps ; i++)
    {
//        _vertices[i] = res[i].m_pos_x;
//        _vertices[i+1] = res[i].m_pos_x;
//        _vertices[i+2] = res[i].m_pos_x;
        //_ps.m_particles[i] = res[i];
        _vertices[i] = res[i].m_pos_x;
        _vertices[i+1] = res[i].m_pos_y;
        _vertices[i+2] = res[i].m_pos_z;
    }

    cudaFree(d_particles);
}
