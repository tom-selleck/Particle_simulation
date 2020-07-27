#include "screen.h"
#include <SDL.h>
#include <string.h>

Screen::Screen():m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL)
{

}
bool Screen::init()
{

    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {

        return false;
    }

    m_window = SDL_CreateWindow("Particle Fire explosion",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);

    if(m_window == NULL)
    {
        SDL_Quit();

        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, screen_width, screen_height);


    if(m_renderer == NULL)
    {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }
    if(m_texture == NULL)
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    m_buffer = new Uint32[screen_width*screen_height];
    //memset(m_buffer, 0, screen_width*screen_height*sizeof(Uint32));

    return true;
};

void Screen::clear()
{
        memset(m_buffer,0, screen_width*screen_height*sizeof(Uint32));
}

void Screen::set_pixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
    if(x < 0 || x >= screen_width || y < 0  || y >= screen_height)
    {
        return;
    }
    Uint32 color = 0;

    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;

    m_buffer[(y*screen_width + x)] = color;
}
void Screen::update_screen()
    {
    SDL_UpdateTexture(m_texture, NULL, m_buffer, screen_width*sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);

    };

bool Screen::process_event()
{
    SDL_Event event;



    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            return false;
        }
    }
    return true;
}
void Screen::close()
{
    delete [] m_buffer;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
};

