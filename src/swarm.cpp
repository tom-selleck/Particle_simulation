#include "swarm.h"

Swarm::Swarm()
{
    //usuwaj wszystko z "new"
    m_p_particles = new Particle[NPARTICLES];

}

void Swarm::update()
{
    for(int i=0; i<Swarm::NPARTICLES; i++)
        {
            m_p_particles[i].update_pos();
        }
}

Swarm::~Swarm()
{
    delete[] m_p_particles;
}
