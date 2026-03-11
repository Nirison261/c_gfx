#include "c_gfx.h"
#include <stdlib.h> // Used for functions like abs(), etc

void c_gfx_init(c_gfx_t *gfx,
                c_gfx_display_t *display)
{
    gfx->display = display;

    gfx->clip_x_min = 0;
    gfx->clip_y_min = 0;
    gfx->clip_x_max = display->width;
    gfx->clip_y_max = display->height;
}

void c_gfx_set_clip(c_gfx_t *gfx,
                    int x,
                    int y,
                    int w, // Don't change this to uint16_t !
                    int h) // Don't change this to uint16_t !
{
    /* Reject empty or negative regions */
    if (w <= 0 || h <= 0)
    {
        gfx->clip_x_min = 0;
        gfx->clip_y_min = 0;
        gfx->clip_x_max = 0;
        gfx->clip_y_max = 0;
        return;
    }

    int x_min = x;
    int y_min = y;
    int x_max = x + w;
    int y_max = y + h;

    /* Clamp against display bounds */
    if (x_min < 0)
        x_min = 0;

    if (y_min < 0)
        y_min = 0;

    if (x_max > gfx->display->width)
        x_max = gfx->display->width;

    if (y_max > gfx->display->height)
        y_max = gfx->display->height;

    /* If fully outside display, collapse to empty region */
    if (x_min >= x_max || y_min >= y_max)
    {
        gfx->clip_x_min = 0;
        gfx->clip_y_min = 0;
        gfx->clip_x_max = 0;
        gfx->clip_y_max = 0;
        return;
    }

    gfx->clip_x_min = x_min;
    gfx->clip_y_min = y_min;
    gfx->clip_x_max = x_max;
    gfx->clip_y_max = y_max;
}

void c_gfx_draw_pixel(c_gfx_t *gfx,
                      int x,
                      int y,
                      uint16_t color)
{
    if (x < gfx->clip_x_min || x >= gfx->clip_x_max)
        return;

    if (y < gfx->clip_y_min || y >= gfx->clip_y_max)
        return;

    gfx->display->draw_pixel(gfx->display, x, y, color);
}

void c_gfx_draw_line(c_gfx_t *gfx,
                     int x0,
                     int y0,
                     int x1,
                     int y1,
                     uint16_t color)
{
    c_gfx_display_t *disp = gfx->display;

    /* Use accelerated line only if:
       - Driver provides it
       - Clip region is full display
    */
    if (disp->draw_line &&
        gfx->clip_x_min == 0 &&
        gfx->clip_y_min == 0 &&
        gfx->clip_x_max == disp->width &&
        gfx->clip_y_max == disp->height)
    {
        disp->draw_line(disp, x0, y0, x1, y1, color);
        return;
    }

    /* Software fallback (Bresenham) */
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