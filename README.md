# c_gfx

Minimal immediate-mode graphics library in C.

## Architecture

Application
    ↓
c_gfx (drawing primitives)
    ↓
Display Interface (c_gfx_display_t)
    ↓
Display Driver (SDL, SSD1331, etc.)
    ↓
Hardware

## Features

- Immediate pixel API
- No framebuffer
- No dynamic allocation
- Portable
- Driver abstraction

## Example

```c
c_gfx_draw_line(&gfx, 0, 0, 50, 50, 0xFFFF);
```