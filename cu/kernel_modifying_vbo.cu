#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

__global__ void modifying_vbo_kernel(float *pos)
{
    unsigned int index = threadIdx.x;
    pos[index] = -0.9f;
}

void modifying_vbo(unsigned int VBO_id) {
    // Register the VBO so that we have a resource CUDA can understand and use
    struct cudaGraphicsResource *cuda_vbo_resource;
    cudaGraphicsGLRegisterBuffer(&cuda_vbo_resource, VBO_id, cudaGraphicsMapFlagsWriteDiscard);

    // Initialize the device pointer we will use to access all the attribute array elements
    float* d_ptr;

    // Map the buffer to make it active for the kernel
    size_t num_bytes;
    cudaGraphicsMapResources(1, &cuda_vbo_resource, 0);

    // Tells the right way to bind the device pointer to the correct resource
    cudaGraphicsResourceGetMappedPointer((void**)&d_ptr, &num_bytes, cuda_vbo_resource);

    // Launch the kernel
    modifying_vbo_kernel<<<1, 9>>>(d_ptr);

    // Unmap the resources so OpenGL can now use the data to render
    cudaGraphicsUnmapResources(1, &cuda_vbo_resource, 0);
}


