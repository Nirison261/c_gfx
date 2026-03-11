cmake_minimum_required(VERSION 3.15)
project(c_gfx VERSION 0.2.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# =====================================================
# Options
# =====================================================
option(C_GFX_BUILD_EXAMPLES "Build SDL examples" ON)
option(C_GFX_BUILD_TESTS "Build unit tests" ON)

# =====================================================
# Core Library
# =====================================================
add_library(c_gfx
    c_gfx.c
)

# Public include so users find c_gfx.h and c_gfx_display.h
target_include_directories(c_gfx PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# =====================================================
# SDL Driver (compiled only if examples enabled)
# =====================================================
if(C_GFX_BUILD_EXAMPLES)
    find_package(SDL2 REQUIRED)

    target_sources(c_gfx PRIVATE
        drivers/sdl/sdl_display.c
    )

    target_include_directories(c_gfx PRIVATE
        ${SDL2_INCLUDE_DIRS}
        drivers/sdl
    )

    target_link_libraries(c_gfx PRIVATE
        ${SDL2_LIBRARIES}
    )
endif()

# =====================================================
# SDL Example Executable
# =====================================================
if(C_GFX_BUILD_EXAMPLES)
    add_executable(c_gfx_sdl_example
        examples/sdl/main.c
    )

    target_include_directories(c_gfx_sdl_example PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        drivers/sdl
    )

    target_link_libraries(c_gfx_sdl_example PRIVATE
        c_gfx
        SDL2::SDL2
    )
endif()

# =====================================================
# Unit Tests
# =====================================================
if(C_GFX_BUILD_TESTS)
    enable_testing()

    add_executable(c_gfx_tests
        tests/test_line.c
        tests/mock_display.c
    )

    target_include_directories(c_gfx_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_link_libraries(c_gfx_tests PRIVATE
        c_gfx
    )

    add_test(
        NAME c_gfx_unit_tests
        COMMAND c_gfx_tests
    )
endif()