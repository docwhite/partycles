// CUDA-C includes
#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "particlesystem.h"
#include "particle.h"

__global__ void advance_particles_kernel(float* d_verts)
{
    int index = threadIdx.x;

    d_verts[index] = 0.8;
    d_verts[index+1] = 0.8;
    d_verts[index+2] = 0.8;
}

// Main cuda function
void advance_particles(ParticleSystem& _ps, float *_vertices) {
    int size_of_ps = _ps.m_particles.size();

    float  h_verts[3 * size_of_ps];
    float* d_verts = NULL;

    cudaMalloc(&d_verts, 3 * size_of_ps * sizeof(float));

    advance_particles_kernel<<<1,size_of_ps>>>(d_verts);

    cudaMemcpy(h_verts, d_verts, 3 * size_of_ps * sizeof(float), cudaMemcpyDeviceToHost);

    for (int i = 0; i < 3 * size_of_ps; i++) {
        _vertices[i] = h_verts[i];

    }

    cudaFree(d_verts);
}
