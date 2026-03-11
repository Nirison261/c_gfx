#include "mock_display.h"
#include <string.h>

static void mock_draw_pixel(c_gfx_display_t *disp,
                            int x,
                            int y,
                            uint16_t color)
{
    mock_display_t *mock = disp->user_data;

    if (x >= MOCK_WIDTH || y >= MOCK_HEIGHT)
        return;

    mock->buffer[y][x] = color;
}

void mock_display_init(mock_display_t *mock,
                       c_gfx_display_t *display)
{
    memset(mock->buffer, 0, sizeof(mock->buffer));

    display->width = MOCK_WIDTH;
    display->height = MOCK_HEIGHT;
    display->draw_pixel = mock_draw_pixel;
    display->user_data = mock;
}

uint16_t mock_get_pixel(mock_display_t *mock,
                        uint16_t x,
                        uint16_t y)
{
    return mock->buffer[y][x];
}
