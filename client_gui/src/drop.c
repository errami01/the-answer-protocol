#include <raylib.h>

Rectangle get_drop_button(Rectangle panel, int i)
{
    return (Rectangle){
        panel.x + panel.width - 45,
        panel.y + 65 + i * 30,
        24,
        24
    };
}

void drop_button(Rectangle button)
{
    DrawRectangleRec(button, RED);
    DrawText("X", button.x + 6, button.y + 3, 18, WHITE);
}
