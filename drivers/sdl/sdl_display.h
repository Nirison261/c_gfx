#ifndef SDL_DISPLAY_H
#define SDL_DISPLAY_H

#include "c_gfx_display.h"
#include <SDL2/SDL.h>

typedef struct
{
    SDL_Window   *window;
    SDL_Renderer *renderer;
    SDL_Texture  *texture;

    uint16_t width;
    uint16_t height;

    c_gfx_display_t interface;

} sdl_display_t;

int sdl_display_init(sdl_display_t *dev,
                        int width,
                        int height);

c_gfx_display_t* sdl_display_get_interface(sdl_display_t *dev);

void sdl_display_present(sdl_display_t *dev);

#endif
