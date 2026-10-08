#include "game_arrow_buttons.h"
#include "game_commands.h"
#include "game_components_utils.h"

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

void handle_item_clicks(t_game *game)
{
    int i;
    Vector2 mouse;

    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        return ;

    mouse = GetMousePosition();

    i = 0;
    while (i < game->current->item_count)
    {
        Rectangle rect = get_item_button(i);

        if (CheckCollisionPointRec(mouse, rect))
        {
            take(game, game->current->items[i]);
            return ;
        }

        i++;
    }
}

void handle_movement_buttons(t_game *game)
{
    Vector2 mouse;
    Rectangle north;
    Rectangle south;
    Rectangle west;
    Rectangle east;

    if (game == NULL || game->current == NULL)
        return ;

    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        return ;

    mouse = GetMousePosition();

    north = get_north_button();
    south = get_south_button();
    west = get_west_button();
    east = get_east_button();

    if (
        game->current->north[0] != '\0'
        && CheckCollisionPointRec(mouse, north)
    )
    {
        move(game, "north");
        return ;
    }

    if (
        game->current->south[0] != '\0'
        && CheckCollisionPointRec(mouse, south)
    )
    {
        move(game, "south");
        return ;
    }

    if (
        game->current->west[0] != '\0'
        && CheckCollisionPointRec(mouse, west)
    )
    {
        move(game, "west");
        return ;
    }

    if (
        game->current->east[0] != '\0'
        && CheckCollisionPointRec(mouse, east)
    )
    {
        move(game, "east");
        return ;
    }
}
