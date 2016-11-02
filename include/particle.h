#ifndef PARTICLE_H
#define PARTICLE_H

class Particle
{
public:
    Particle();
    void step();
    int m_value;
    float m_pos_x;
    float m_pos_y;
    float m_pos_z;
    float m_vel_x;
    float m_vel_y;
    float m_vel_z;
};

#endif // PARTICLE_H
