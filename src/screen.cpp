#include "screen.h"
#include <SDL.h>
#include <string.h>

Screen::Screen():m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer_1(NULL), m_buffer_2(NULL)
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

    m_buffer_1 = new Uint32[screen_width*screen_height];
    m_buffer_2 = new Uint32[screen_width*screen_height];

    //memset(m_buffer, 0, screen_width*screen_height*sizeof(Uint32));

    return true;
};

void Screen::box_blur()
{
    //swap buffers, so pixel is in m_buffer_2 and we are drawing to m_buffer_2
    Uint32 *temp_buff = m_buffer_1;
    m_buffer_1 = m_buffer_2;
    m_buffer_2 = temp_buff;

    for(int y=0; y<screen_height; y++)
    {
        for(int x=0; x<screen_width; x++)
        {
            int red_ttl = 0;
            int green_ttl = 0;
            int blue_ttl = 0;


            for(int row=-1; row<=1; row++)
            {
                for(int col=-1; col<=1; col++)
                {
                    int cur_x = x + col;
                    int cur_y = y + row;

                    if(cur_x >= 0 && cur_x < screen_width && cur_y >= 0 && cur_y < screen_height)
                    {
                        Uint32 color = m_buffer_2[cur_y*screen_width+cur_x];

                        Uint8 red = color >> 24;
                        Uint8 green = color >> 16;
                        Uint8 blue = color >>8;

                        red_ttl += red;
                        green_ttl += green;
                        blue_ttl += blue;
                    }
                }
            }

            Uint8 red = red_ttl/9;
            Uint8 green = green_ttl/9;
            Uint8 blue = blue_ttl/9;
            set_pixel(x, y, red, green, blue);
        }
    }
}
/*
void Screen::clear()
{
        memset(m_buffer_1,0, screen_width*screen_height*sizeof(Uint32));
        memset(m_buffer_2,0, screen_width*screen_height*sizeof(Uint32));
}
*/
void Screen::set_pixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
    if(x < 0 || x >= screen_width || y < 0  || y >= screen_height)
    {
        return;
    }
    Uint32 color = 0;

    //RGBA

    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;

    m_buffer_1[(y*screen_width + x)] = color;
}
void Screen::update_screen()
    {
    SDL_UpdateTexture(m_texture, NULL, m_buffer_1, screen_width*sizeof(Uint32));
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
    delete [] m_buffer_1;
    delete [] m_buffer_2;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
};

