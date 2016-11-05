#include <iostream>

#include "particle.h"

Particle::Particle()
{
    m_pos_x = 0.4f;
    m_pos_y = 0.4f;
    m_pos_z = 0.0f;
    m_vel_x = (((float) rand() / (RAND_MAX))-0.5) * 0.01f;
    m_vel_y = (((float) rand() / (RAND_MAX))-0.5) * 0.01f;
    m_vel_z = (((float) rand() / (RAND_MAX))-0.5) * 0.01f;
}

__device__
void Particle::step()
{
    m_pos_x += m_vel_x;
    m_pos_y += m_vel_y;
    m_pos_z += m_vel_z;
}
