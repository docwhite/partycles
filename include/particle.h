#ifndef PARTICLE_H
#define PARTICLE_H

#ifdef __CUDACC__
#define CUDA_HOST __host__
#define CUDA_DEVICE __device__
#define CUDA_HOST_AND_DEVICE __host__ __device__
#else
#define CUDA_HOST
#define CUDA_DEVICE
#define CUDA_HOST_AND_DEVICE
#endif

class Particle
{
public:
    Particle();
    CUDA_DEVICE void step();
    float m_pos_x;
    float m_pos_y;
    float m_pos_z;
    float m_vel_x;
    float m_vel_y;
    float m_vel_z;
};

#endif // PARTICLE_H
