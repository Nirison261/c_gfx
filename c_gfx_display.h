#ifndef C_GFX_DISPLAY_H
#define C_GFX_DISPLAY_H

#include <stdint.h>

typedef struct c_gfx_display
{
    /* Mandatory properties */
    uint16_t width;
    uint16_t height;

    /* Mandatory function */
    void (*draw_pixel)(
        struct c_gfx_display *disp,
        uint16_t x,
        uint16_t y,
        uint16_t color);

    /* Optional accelerated primitives */
    void (*draw_line)(
        struct c_gfx_display *disp,
        uint16_t x0, uint16_t y0,
        uint16_t x1, uint16_t y1,
        uint16_t color);

    void (*fill_rect)(
        struct c_gfx_display *disp,
        uint16_t x, uint16_t y,
        uint16_t w, uint16_t h,
        uint16_t color);

    /* Frame control (optional but recommended) */
    void (*flush)(struct c_gfx_display *disp);

    /* Driver specific data/context */
    void *user_data;

} c_gfx_display_t;

#endif