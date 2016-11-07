#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

#include <iostream>

#include "particlesystem.h"

__global__ void modifying_vbo_kernel(float *d_vbo_positions, float *d_ps_positions, float *d_ps_velocities, int num_of_elements_per_array)
{
    unsigned int index = blockDim.x * blockIdx.x + threadIdx.x;
    if (index < num_of_elements_per_array)
    {
    d_ps_positions[index] += d_ps_velocities[index];

    if (d_ps_positions[index] > 1.0f || d_ps_positions[index] < -1.0f)
        d_ps_velocities[index] = -d_ps_velocities[index];

    d_vbo_positions[index] = d_ps_positions[index];
    }
}

void modifying_vbo(unsigned int VBO_id, ParticleSystem* ps) {
    // Register the VBO so that we have a resource CUDA can understand and use
    struct cudaGraphicsResource *cuda_vbo_resource;
    cudaGraphicsGLRegisterBuffer(&cuda_vbo_resource, VBO_id, cudaGraphicsMapFlagsWriteDiscard);

    // Initialize the device pointer we will use to access all the attribute array elements
    float* d_vbo_positions;
    float* d_ps_positions = thrust::raw_pointer_cast(&ps->positions[0]);
    float* d_ps_velocities = thrust::raw_pointer_cast(&ps->velocities[0]);

    // Map the buffer to make it active for the kernel
    size_t num_bytes;
    cudaGraphicsMapResources(1, &cuda_vbo_resource, 0);

    // Tells the right way to bind the device pointer to the correct resource
    cudaGraphicsResourceGetMappedPointer((void**)&d_vbo_positions, &num_bytes, cuda_vbo_resource);

    // std::cout << num_bytes / sizeof(float) << std::endl;

    unsigned int num_of_elements_per_array = 3 * ps->numParts;
    unsigned int block_size = 1024;
    unsigned int grid_size = num_of_elements_per_array / block_size + 1;

//    std::cout << "Number of elements in array: " << num_of_elements_per_array << std::endl;
//    std::cout << "Grid size: " << grid_size << std::endl;
//    std::cout << "Block size: " << block_size << std::endl;

    // Launch the kernel
    modifying_vbo_kernel<<<grid_size, block_size>>>(d_vbo_positions, d_ps_positions, d_ps_velocities, num_of_elements_per_array);


    // Unmap the resources so OpenGL can now use the data to render
    cudaGraphicsUnmapResources(1, &cuda_vbo_resource, 0);
}


