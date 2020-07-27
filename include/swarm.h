#ifndef SWARM_H
#define SWARM_H
#include "particle.h"

class Swarm
{
    public:
        Swarm();
        virtual ~Swarm();
        const static int NPARTICLES = 5000;
        void update();

        const Particle * const get_particles()
        {
            return m_p_particles;
        };
    protected:

    private:
         Particle *m_p_particles;
};

#endif // SWARM_H
