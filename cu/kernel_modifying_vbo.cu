#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

__global__ void modifying_vbo_kernel(float *pos)
{
    unsigned int index = threadIdx.x;
    pos[index] = 0.9f;
}


// Main cuda function
void modifying_vbo(unsigned int VBO_id) {
    struct cudaGraphicsResource *cuda_vbo_resource;
    void *d_vbo_buffer = NULL;
    cudaGraphicsGLRegisterBuffer(&cuda_vbo_resource, VBO_id, cudaGraphicsMapFlagsWriteDiscard);
    float* d_ptr;
    cudaGraphicsMapResources(1, &cuda_vbo_resource, 0);
    size_t num_bytes;
    cudaGraphicsResourceGetMappedPointer((void**)&d_ptr, &num_bytes, cuda_vbo_resource);
    modifying_vbo_kernel<<<1, 9>>>(d_ptr);
    cudaGraphicsUnmapResources(1, &cuda_vbo_resource, 0);
}


