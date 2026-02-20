#ifndef MOCK_DISPLAY_H
#define MOCK_DISPLAY_H

#include "c_gfx_display.h"
#include <stdint.h>

#define MOCK_WIDTH  64
#define MOCK_HEIGHT 64

typedef struct {
    uint16_t buffer[MOCK_HEIGHT][MOCK_WIDTH];
} mock_display_t;

void mock_display_init(mock_display_t *mock,
                       c_gfx_display_t *display);

uint16_t mock_get_pixel(mock_display_t *mock,
                        uint16_t x,
                        uint16_t y);

#endif
