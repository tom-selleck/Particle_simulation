#include "swarm.h"

Swarm::Swarm():last_time(0)
{
    //usuwaj wszystko z "new"
    m_p_particles = new Particle[NPARTICLES];

}

void Swarm::update(int elapsed)
{
    int interval = elapsed - last_time;
    for(int i=0; i<Swarm::NPARTICLES; i++)
        {
            m_p_particles[i].update_pos(interval);
        };
        last_time = elapsed;
}

Swarm::~Swarm()
{
    delete[] m_p_particles;
}
