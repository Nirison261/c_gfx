#ifndef C_GFX_H
#define C_GFX_H

#include <stdint.h>
#include "c_gfx_display.h"

typedef struct {

    c_gfx_display_t *display;

    int clip_x_min;
    int clip_y_min;
    int clip_x_max;
    int clip_y_max;

} c_gfx_t;

void c_gfx_init(c_gfx_t *gfx,
                c_gfx_display_t *display);

void c_gfx_set_clip(c_gfx_t *gfx,
                    int x,
                    int y,
                    int w, // Don't change this to uint16_t !
                    int h); // Don't change this to uint16_t !

void c_gfx_draw_pixel(c_gfx_t *gfx,
                      int x,
                      int y,
                      uint16_t color);

void c_gfx_draw_line(c_gfx_t *gfx,
                     int x0,
                     int y0,
                     int x1,
                     int y1,
                     uint16_t color);

#endif
