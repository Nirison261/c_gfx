#ifndef C_GFX_DISPLAY_H
#define C_GFX_DISPLAY_H

#include <stdint.h>

typedef struct {

    uint16_t width;
    uint16_t height;

    void (*draw_pixel)(void *ctx,
                       uint16_t x,
                       uint16_t y,
                       uint16_t color);

    void *ctx;

} c_gfx_display_t;

#endif