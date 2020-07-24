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

    Uint32 *m_buffer = new Uint32[screen_width*screen_height];

    memset(m_buffer, 0, screen_height*screen_width*sizeof(Uint32));

    for(int i = 0; i<screen_height*screen_width; i++)
    {
        m_buffer[i] = 0x0000FFFF;
    }
    SDL_UpdateTexture(m_texture, NULL, m_buffer, screen_width*sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
    return true;
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

