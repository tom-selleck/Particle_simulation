#include <iostream>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include "screen.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "swarm.h"
using namespace std;

int main(int argc, char *argv[])
{

    //random number generator seeded with time function
    srand(time(NULL));

    Screen screen;
    if(screen.init()==false)
    {
        cout << "Error initializig SDL!" << endl;
    }

    Swarm swarm;

    while(true)
    {
        //update particles
    screen.clear();
    swarm.update();
        //draw particles

    int elapsed = SDL_GetTicks();

    unsigned char red = (1+sin(elapsed*0.0001))*128;
    unsigned char green = (1+sin(elapsed*0.0002))*128;
    unsigned char blue = (1+sin(elapsed*0.0003))*128;

    //cout << red << " " << green << " " << blue << endl;



        const Particle * const p_particles = swarm.get_particles();

        for(int i=0; i<Swarm::NPARTICLES; i++)
        {
            Particle particle = p_particles[i];

            int x = (particle.m_x +1) * Screen::screen_width/2;
            int y = particle.m_y * Screen::screen_width/2 + Screen::screen_height/2;

            screen.set_pixel(x, y, red, green, blue);
        }

        // draw on the screen
       screen.update_screen();\

        //check for events
        if(screen.process_event() == false)
        {
            break;
        }

    }
   //displays highest value of green

   screen.close();

    return 0;
}
