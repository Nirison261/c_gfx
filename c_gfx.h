#ifndef C_GFX_H
#define C_GFX_H

#include <stdint.h>
#include "c_gfx_display.h"

typedef struct {

    c_gfx_display_t *display;

    uint16_t clip_x;
    uint16_t clip_y;
    uint16_t clip_w;
    uint16_t clip_h;

} c_gfx_t;

void c_gfx_init(c_gfx_t *gfx,
                c_gfx_display_t *display);

void c_gfx_set_clip(c_gfx_t *gfx,
                    uint16_t x,
                    uint16_t y,
                    uint16_t w,
                    uint16_t h);

void c_gfx_draw_pixel(c_gfx_t *gfx,
                      uint16_t x,
                      uint16_t y,
                      uint16_t color);

void c_gfx_draw_line(c_gfx_t *gfx,
                     uint16_t x0,
                     uint16_t y0,
                     uint16_t x1,
                     uint16_t y1,
                     uint16_t color);

#endif
