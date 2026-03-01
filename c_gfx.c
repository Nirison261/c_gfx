#include "c_gfx.h"
#include <stdlib.h> // Used for functions like abs(), etc

void c_gfx_init(c_gfx_t *gfx,
                c_gfx_display_t *display)
{
    gfx->display = display;

    gfx->clip_x = 0;
    gfx->clip_y = 0;
    gfx->clip_w = display->width;
    gfx->clip_h = display->height;
}

void c_gfx_set_clip(c_gfx_t *gfx,
                    uint16_t x,
                    uint16_t y,
                    uint16_t w,
                    uint16_t h)
{
    gfx->clip_x = x;
    gfx->clip_y = y;
    gfx->clip_w = w;
    gfx->clip_h = h;
}

void c_gfx_draw_pixel(c_gfx_t *gfx,
                      uint16_t x,
                      uint16_t y,
                      uint16_t color)
{
    if (x < gfx->clip_x || y < gfx->clip_y)
        return;

    if (x >= gfx->clip_x + gfx->clip_w)
        return;

    if (y >= gfx->clip_y + gfx->clip_h)
        return;

    gfx->display->draw_pixel(gfx->display, x, y, color);
}

void c_gfx_draw_line(c_gfx_t *gfx,
                     uint16_t x0,
                     uint16_t y0,
                     uint16_t x1,
                     uint16_t y1,
                     uint16_t color)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (1)
    {
        c_gfx_draw_pixel(gfx, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }

        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}