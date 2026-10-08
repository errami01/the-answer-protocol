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

static int get_npc_start_y(t_game *game)
{
    int items_start_y;
    int items_height;

    items_start_y = 50;

    items_height =
        game->current->item_count
        * (LIST_HEIGHT + LIST_SPACING);

    return (items_start_y + items_height + 30);
}

Rectangle get_npc_button(t_game *game, int index)
{
    int start_y;

    start_y = get_npc_start_y(game);

    return ((Rectangle){
        GetScreenWidth() - LIST_WIDTH - LIST_MARGIN,
        start_y + 30 + index * (LIST_HEIGHT + LIST_SPACING),
        LIST_WIDTH,
        LIST_HEIGHT
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

void draw_npcs(t_game *game)
{
    int i;
    int start_y;

    start_y = get_npc_start_y(game);

    DrawText(
        "NPCs",
        GetScreenWidth() - 200,
        start_y,
        20,
        BLACK
    );

    i = 0;
    while (i < game->current->npc_count)
    {
        Rectangle rect = get_npc_button(game, i);
        Vector2 mouse = GetMousePosition();
        Color color = LIGHTGRAY;

        if (CheckCollisionPointRec(mouse, rect))
        {
            color = GRAY;

            // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            //     talk(game, game->current->npcs[i]);
        }

        DrawRectangleRec(rect, color);
        DrawRectangleLinesEx(rect, 1, DARKGRAY);

        DrawText(
            game->current->npcs[i],
            rect.x + 10,
            rect.y + 8,
            16,
            BLACK
        );

        i++;
    }
}
