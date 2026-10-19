#include "quests.h"
#include "game.h"
#include "game_utils.h"

int parse_quests(const char *response, t_game *game)
{
    const char  *pos;
    const char  *end;
    char        object[512];
    size_t      len;
    int         count;

    if (!response || !game)
        return (-1);

    if (strncmp(response, "OK ", 3) == 0)
        response += 3;

    pos = strchr(response, '[');
    if (!pos)
        return (-1);

    pos++;
    count = 0;

    while (*pos && *pos != ']' && count < MAX_QUESTS)
    {
        while (*pos == ' ' || *pos == '\t' || *pos == ',')
            pos++;

        if (*pos == ']')
            break ;

        if (*pos != '{')
            return (-1);

        end = strchr(pos, '}');
        if (!end)
            return (-1);

        len = end - pos + 1;

        if (len >= sizeof(object))
            return (-1);

        memcpy(object, pos, len);
        object[len] = '\0';

        memset(&game->quests[count], 0, sizeof(t_quest));

        if (extract_json_string(
                object,
                "\"id\"",
                game->quests[count].id,
                sizeof(game->quests[count].id)) < 0)
            return (-1);

        if (extract_json_string(
                object,
                "\"status\"",
                game->quests[count].status,
                sizeof(game->quests[count].status)) < 0)
            return (-1);

        count++;
        pos = end + 1;
    }

    game->quest_count = count;

    return (0);
}

void draw_quests(t_game *game)
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

    panel_width = 500;
    panel_height = 400;

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

    DrawText(
        "Quests",
        panel_x + (panel_width - MeasureText("Quests", 28)) / 2,
        panel_y + 20,
        28,
        BLACK
    );

    if (game->quest_count == 0)
    {
        DrawText(
            "No active quests",
            panel_x
                + (panel_width - MeasureText("No active quests", 18)) / 2,
            panel_y + 100,
            18,
            GRAY
        );

        return ;
    }

    i = 0;
    while (i < game->quest_count)
    {
        Rectangle quest_rect = {
            panel_x + 30,
            panel_y + 80 + i * 60,
            panel_width - 60,
            50
        };

        DrawRectangleRec(
            quest_rect,
            LIGHTGRAY
        );

        DrawRectangleLinesEx(
            quest_rect,
            1,
            DARKGRAY
        );

        DrawText(
            game->quests[i].id,
            quest_rect.x + 10,
            quest_rect.y + 7,
            18,
            BLACK
        );

        DrawText(
            TextFormat("Status: %s", game->quests[i].status),
            quest_rect.x + 10,
            quest_rect.y + 28,
            14,
            DARKGRAY
        );

        i++;
    }
}
