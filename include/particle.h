#ifndef PARTICLE_H
#define PARTICLE_H


struct Particle
{
    double m_x;
    double m_y;

    double m_speed;
    double m_direction;

    public:
        Particle();
        virtual ~Particle();
        void update_pos();

    protected:

    private:

};

#endif // PARTICLE_H
