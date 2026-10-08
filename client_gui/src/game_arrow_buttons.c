#include "game_arrow_buttons.h"
#include <raylib.h>

Rectangle get_north_button(void)
{
    int cx = GetScreenWidth() / 2;
    int cy = GetScreenHeight() / 2;

    Rectangle x = {cx - 60, cy - 140, 120, 60};

    return (x);
}

Rectangle get_south_button(void)
{
    int cx = GetScreenWidth() / 2;
    int cy = GetScreenHeight() / 2;

    Rectangle x = {cx - 60, cy + 80, 120, 60};

    return (x);
}

Rectangle get_west_button(void)
{
    int cx = GetScreenWidth() / 2;
    int cy = GetScreenHeight() / 2;

    Rectangle x = {cx - 220, cy - 30, 120, 60};

    return (x);
}

Rectangle get_east_button(void)
{
    int cx = GetScreenWidth() / 2;
    int cy = GetScreenHeight() / 2;

    Rectangle x = {cx + 100, cy - 30, 120, 60};

    return (x);
}
