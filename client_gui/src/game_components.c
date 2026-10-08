#include "game_components.h"
#include "game_commands.h"
#include <raylib.h>

static Rectangle get_item_button(int index)
{
    const int width = 180;
    const int height = 32;
    const int spacing = 8;
    const int margin = 20;

    return ((Rectangle){
        GetScreenWidth() - width - margin,
        50 + index * (height + spacing),
        width,
        height
    });
}

void draw_items(t_game *game)
{
    int i;

    DrawText(
        "Items",
        GetScreenWidth() - 200,
        20,
        20,
        BLACK
    );

    i = 0;
    while (i < game->current->item_count)
    {
        Rectangle rect = get_item_button(i);
        Vector2 mouse = GetMousePosition();

        Color color = LIGHTGRAY;

        if (CheckCollisionPointRec(mouse, rect))
        {
            color = GRAY;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                take(game, game->current->items[i]);
        }

        DrawRectangleRec(rect, color);
        DrawRectangleLinesEx(rect, 1, DARKGRAY);

        DrawText(
            game->current->items[i],
            rect.x + 10,
            rect.y + 8,
            16,
            BLACK
        );

        i++;
    }
}
