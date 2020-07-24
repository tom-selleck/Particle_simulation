#ifndef SCREEN_H
#define SCREEN_H
#include <SDL.h>

class Screen
{
    public:
        const static int screen_width = 800;
        const static int screen_height = 600;

    protected:

    private:
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;
        SDL_Texture *m_texture;
        Uint32 *m_buffer;


    public:
        Screen();
        bool init();
        bool process_event();
        void close();


};

#endif // SCREEN_H
