#include "c_gfx.h"

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

    gfx->display->draw_pixel(gfx->display->ctx, x, y, color);
}
