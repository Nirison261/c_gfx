#include "sdl_display.h"
#include "c_gfx_display.h"
#include <stdio.h>

static void sdl_draw_pixel(c_gfx_display_t *disp,
                           uint16_t x,
                           uint16_t y,
                           uint16_t color)
{
    sdl_display_t *dev = disp->user_data;

    uint8_t r = (color >> 11) & 0x1F;
    uint8_t g = (color >> 5)  & 0x3F;
    uint8_t b =  color        & 0x1F;

    r = (r * 255) / 31;
    g = (g * 255) / 63;
    b = (b * 255) / 31;

    SDL_SetRenderDrawColor(dev->renderer, r, g, b, 255);
    SDL_RenderDrawPoint(dev->renderer, x, y);
}

int sdl_display_init(sdl_display_t *dev, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return -1;

    dev->width  = width;
    dev->height = height;

    dev->window = SDL_CreateWindow("c_gfx SDL",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    width,
                                    height,
                                    0);
    
    if (!dev->window)
        return -1;
    
    dev->renderer = SDL_CreateRenderer(dev->window,
                                       -1,
                                       SDL_RENDERER_ACCELERATED);

    if (!dev->renderer)
        return -1;
    
    dev->texture = SDL_CreateTexture(
        dev->renderer,
        SDL_PIXELFORMAT_RGB565,
        SDL_TEXTUREACCESS_STREAMING,
        width,
        height);

    if (!dev->texture)
        return -1;

    // Setup interface
    dev->interface.width  = width;
    dev->interface.height = height;
    dev->interface.user_data = dev;
    dev->interface.draw_pixel = sdl_draw_pixel;

    return 0;
}

c_gfx_display_t* sdl_display_get_interface(sdl_display_t *dev)
{
    return &dev->interface;
}

void sdl_display_present(sdl_display_t *dev)
{
    SDL_RenderPresent(dev->renderer);
}
