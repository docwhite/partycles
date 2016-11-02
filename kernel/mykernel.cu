// CUDA-C includes
#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include "particle.h"

//Adds two arrays
extern "C"
void runCudaPart(Particle* pArray);

__global__ void addAry( int * ary1, int * ary2 )
{
    int indx = threadIdx.x;
    ary1[ indx ] += ary2[ indx ];
}

// Main cuda function
void runCudaPart(Particle* pArray) {

    int ary1[32];
    int ary2[32];
    int res[32];

    for( int i=0 ; i<32 ; i++ )
    {
        ary1[i] = i;
        ary2[i] = 2*i;
        res[i]=0;
    }

    int* d_ary1;
    int* d_ary2;

    cudaMalloc((void**)&d_ary1, 32*sizeof(int));
    cudaMalloc((void**)&d_ary2, 32*sizeof(int));

    cudaMemcpy((void*)d_ary1, (void*)ary1, 32*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy((void*)d_ary2, (void*)ary2, 32*sizeof(int), cudaMemcpyHostToDevice);

    addAry<<<1,32>>>(d_ary1,d_ary2);

    cudaMemcpy((void*)res, (void*)d_ary1, 32*sizeof(int), cudaMemcpyDeviceToHost);
    for( int i=0 ; i<32 ; i++ )
        pArray[i].m_value = res[i];

    cudaFree(d_ary1);
    cudaFree(d_ary2);
}
