#include <SDL2/SDL.h>
#include "c_gfx.h"
#include "sdl_display.h"

int main(void)
{
    sdl_display_t sdl_dev;
    c_gfx_display_t display;
    c_gfx_t gfx;

    if (sdl_display_init(&sdl_dev, 320, 240) != 0)
        return -1;

    sdl_display_create(&sdl_dev, &display);
    c_gfx_init(&gfx, &display);

    // Draw demo scene
    for (int i = 0; i < 320; i += 10)
        c_gfx_draw_line(&gfx, 0, 0, i, 239, 0xF800);

    for (int i = 0; i < 240; i += 10)
        c_gfx_draw_line(&gfx, 0, 0, 319, i, 0x07E0);

    sdl_display_present(&sdl_dev);

    int running = 1;
    SDL_Event e;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = 0;
        }
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}
