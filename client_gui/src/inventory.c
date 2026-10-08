#include <raylib.h>
#include "inventory.h"
#include "game.h"

void draw_inventory(char **items)
{
    int screen_width;
    int screen_height;
    int panel_width;
    int panel_height;
    int panel_x;
    int panel_y;
    int i;

    screen_width = GetScreenWidth();
    screen_height = GetScreenHeight();

    DrawRectangle(
        0,
        0,
        screen_width,
        screen_height,
        Fade(BLACK, 0.55f)
    );

    panel_width = 400;
    panel_height = 350;

    panel_x = (screen_width - panel_width) / 2;
    panel_y = (screen_height - panel_height) / 2;

    DrawRectangle(
        panel_x,
        panel_y,
        panel_width,
        panel_height,
        RAYWHITE
    );

    DrawRectangleLinesEx(
        (Rectangle){
            panel_x,
            panel_y,
            panel_width,
            panel_height
        },
        2,
        DARKGRAY
    );

    const char *title = "Inventory";

    DrawText(
        title,
        panel_x + (panel_width - MeasureText(title, 28)) / 2,
        panel_y + 20,
        28,
        BLACK
    );

    if (items == NULL || items[0] == NULL)
    {
        const char *empty = "Inventory is empty";

        DrawText(
            empty,
            panel_x + (panel_width - MeasureText(empty, 18)) / 2,
            panel_y + 100,
            18,
            GRAY
        );

        return ;
    }

    i = 0;
    while (items[i] != NULL)
    {
        DrawText(
            items[i],
            panel_x + 30,
            panel_y + 80 + i * 30,
            20,
            BLACK
        );

        i++;
    }
}

void clear_inventory(t_game *game)
{
    int i;

    i = 0;
    while (i < MAX_INVENTORY && game->inventory[i] != NULL)
    {
        free(game->inventory[i]);
        game->inventory[i] = NULL;
        i++;
    }
}

int parse_inventory(const char *response, t_game *game)
{
    const char  *pos;
    const char  *start;
    const char  *end;
    size_t      len;
    int         count;

    if (!response || !game)
        return (-1);

    clear_inventory(game);

    if (strncmp(response, "OK ", 3) == 0)
        response += 3;

    pos = strchr(response, '[');
    if (!pos)
        return (-1);

    pos++;
    count = 0;

    while (*pos && *pos != ']' && count < MAX_INVENTORY)
    {
        while (*pos == ' ' || *pos == '\t' || *pos == ',')
            pos++;

        if (*pos == ']')
            break ;

        if (*pos != '"')
            return (-1);

        start = ++pos;
        end = strchr(start, '"');

        if (!end)
            return (-1);

        len = end - start;

        game->inventory[count] = malloc(len + 1);
        if (!game->inventory[count])
        {
            clear_inventory(game);
            return (-1);
        }

        memcpy(game->inventory[count], start, len);
        game->inventory[count][len] = '\0';

        count++;
        pos = end + 1;
    }

    game->inventory[count] = NULL;

    return (0);
}
