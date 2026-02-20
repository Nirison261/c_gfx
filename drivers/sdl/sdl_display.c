#include "sdl_display.h"
#include <stdio.h>

static void sdl_draw_pixel(void *ctx,
                           uint16_t x,
                           uint16_t y,
                           uint16_t color)
{
    sdl_display_t *dev = (sdl_display_t *)ctx;

    uint8_t r = (color >> 11) & 0x1F;
    uint8_t g = (color >> 5)  & 0x3F;
    uint8_t b =  color        & 0x1F;

    r = (r * 255) / 31;
    g = (g * 255) / 63;
    b = (b * 255) / 31;

    SDL_SetRenderDrawColor(dev->renderer, r, g, b, 255);
    SDL_RenderDrawPoint(dev->renderer, x, y);
}

int sdl_display_init(sdl_display_t *dev,
                     uint16_t width,
                     uint16_t height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return -1;

    dev->width = width;
    dev->height = height;

    dev->window = SDL_CreateWindow("c_gfx",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    width,
                                    height,
                                    0);

    dev->renderer = SDL_CreateRenderer(dev->window,
                                       -1,
                                       SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(dev->renderer, 0, 0, 0, 255);
    SDL_RenderClear(dev->renderer);

    return 0;
}

void sdl_display_create(sdl_display_t *dev,
                        c_gfx_display_t *display)
{
    display->width  = dev->width;
    display->height = dev->height;
    display->draw_pixel = sdl_draw_pixel;
    display->ctx = dev;
}

void sdl_display_present(sdl_display_t *dev)
{
    SDL_RenderPresent(dev->renderer);
}
