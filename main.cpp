#include <iostream>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include "screen.h"

using namespace std;

int main(int argc, char *argv[])
{

    Screen screen;
    if(screen.init()==false)
    {
        cout << "Error initializig SDL!" << endl;
    }

    while(true)
    {
        //update particles
        //draw particles
        //check for events/messages
        if(screen.process_event() == false)
        {
            break;
        }

    }
   screen.close();

    return 0;
}
