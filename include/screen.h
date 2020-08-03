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
        Uint32 *m_buffer_1;
        Uint32 *m_buffer_2;


    public:
        Screen();
        bool init();
        void set_pixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
        void update_screen();
        bool process_event();
        void close();
        void clear();
        void box_blur();



};

#endif // SCREEN_H
