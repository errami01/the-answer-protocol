#include "hp.h"
#include <stdlib.h>

int extract_json_int(const char *json, const char *key, int *value)
{
    const char  *pos;

    pos = strstr(json, key);
    if (pos == NULL)
        return (-1);

    pos = strchr(pos, ':');
    if (pos == NULL)
        return (-1);

    pos++;

    while (*pos == ' ' || *pos == '\t')
        pos++;

    *value = atoi(pos);

    return (0);
}

int parse_status(char *response, t_game *game)
{
    if (extract_json_int(response, "\"hp\"", &game->hp) < 0 || extract_json_int(response, "\"max_hp\"", &game->max_hp) < 0)
        return (-1);

    return (0);
}

void draw_hp_bar(t_game *game)
{
    const int bar_width = 220;
    const int bar_height = 24;
    const int margin = 20;

    int x;
    int y;

    float ratio;
    int filled_width;

    char text[64];

    x = margin;
    y = GetScreenHeight() - bar_height - margin;

    if (game->max_hp <= 0)
        ratio = 0.0f;
    else
        ratio = (float)game->hp / (float)game->max_hp;

    if (ratio < 0.0f)
        ratio = 0.0f;
    if (ratio > 1.0f)
        ratio = 1.0f;

    filled_width = (int)(bar_width * ratio);

    /*
    ** Background
    */
    DrawRectangle(
        x,
        y,
        bar_width,
        bar_height,
        DARKGRAY
    );

    /*
    ** Current HP
    */
    DrawRectangle(
        x,
        y,
        filled_width,
        bar_height,
        RED
    );

    /*
    ** Border
    */
    DrawRectangleLines(
        x,
        y,
        bar_width,
        bar_height,
        BLACK
    );

    /*
    ** HP text
    */
    snprintf(
        text,
        sizeof(text),
        "%d / %d HP",
        game->hp,
        game->max_hp
    );

    DrawText(
        text,
        x + 8,
        y + 4,
        16,
        WHITE
    );
}
