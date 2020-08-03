#ifndef PARTICLE_H
#define PARTICLE_H


struct Particle
{
    double m_x;
    double m_y;


    public:
        Particle();
        virtual ~Particle();
        void update_pos(int interval);


    protected:

    private:
    double m_speed;
    double m_direction;
    void init();

};

#endif // PARTICLE_H
