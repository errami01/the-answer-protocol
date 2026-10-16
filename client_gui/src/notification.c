#include "notification.h"

void show_notification(t_game *game, const char *text)
{
    strncpy(
        game->notification,
        text,
        sizeof(game->notification) - 1
    );
    game->notification[sizeof(game->notification) - 1] = '\0';
    game->notification_time = GetTime();
}

void draw_notification(t_game *game)
{
    double elapsed;
    float alpha;

    int font_size;
    int text_width;
    int x;
    int y;

    Color color;

    if (game->notification[0] == '\0')
        return ;

    elapsed = GetTime() - game->notification_time;

    if (elapsed >= DURATION)
    {
        game->notification[0] = '\0';
        return ;
    }

    if (elapsed < 3.0)
        alpha = 1.0f;
    else
        alpha = (float)((DURATION - elapsed) / 2.0);

    font_size = 20;

    text_width = MeasureText(
        game->notification,
        font_size
    );

    x = (GetScreenWidth() - text_width) / 2;
    y = GetScreenHeight() - 90;

    color = Fade(BLACK, alpha);

    DrawText(
        game->notification,
        x,
        y,
        font_size,
        color
    );
}
