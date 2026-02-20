#include <stdio.h>
#include "c_gfx.h"
#include "mock_display.h"

int main(void)
{
    mock_display_t mock;
    c_gfx_display_t display;
    c_gfx_t gfx;

    mock_display_init(&mock, &display);
    c_gfx_init(&gfx, &display);

    c_gfx_draw_line(&gfx, 0, 0, 10, 0, 0xFFFF);

    // Validate horizontal line
    for (int x = 0; x <= 10; x++)
    {
        if (mock_get_pixel(&mock, x, 0) != 0xFFFF)
        {
            printf("Test failed at x=%d\n", x);
            return 1;
        }
    }

    printf("test_line passed\n");
    return 0;
}
