#include "npc.h"

static Rectangle get_npc_dialog(void)
{
    const int width = 500;
    const int height = 300;

    return ((Rectangle){
        (GetScreenWidth() - width) / 2,
        (GetScreenHeight() - height) / 2,
        width,
        height
    });
}

static void draw_text_field(t_game *game, Rectangle dialog)
{
    Rectangle text_field;
    
    text_field = (Rectangle){
        dialog.x + 30,
        dialog.y + 170,
        dialog.width - 60,
        90
    };
    
    DrawRectangleRec(
        text_field,
        (Color){245, 245, 245, 255}
    );
    
    DrawRectangleLinesEx(
        text_field,
        1,
        DARKGRAY
    );
    
    if (game->npc_response[0] != '\0')
    {
        DrawText(
            game->npc_response,
            text_field.x + 10,
            text_field.y + 10,
            18,
            BLACK
        );
    }
    else
    {
        DrawText(
            "Select an action...",
            text_field.x + 10,
            text_field.y + 10,
            18,
            GRAY
        );
    }
}

void draw_npc_dialog(t_game *game)
{
    Rectangle dialog;
    Rectangle talk_btn;
    Rectangle quest_btn;
    Rectangle attack_btn;
    Rectangle close_btn;

    Vector2 mouse;

    dialog = get_npc_dialog();
    mouse = GetMousePosition();

    DrawRectangle(
        0,
        0,
        GetScreenWidth(),
        GetScreenHeight(),
        Fade(BLACK, 0.55f)
    );

    DrawRectangleRec(dialog, RAYWHITE);
    DrawRectangleLinesEx(dialog, 2, DARKGRAY);

    DrawText(
        game->selected_npc,
        dialog.x + 20,
        dialog.y + 20,
        24,
        BLACK
    );

    close_btn = (Rectangle){
        dialog.x + dialog.width - 40,
        dialog.y + 10,
        30,
        30
    };

    DrawRectangleRec(
        close_btn,
        CheckCollisionPointRec(mouse, close_btn)
            ? LIGHTGRAY
            : RAYWHITE
    );

    DrawText(
        "X",
        close_btn.x + 8,
        close_btn.y + 4,
        20,
        BLACK
    );

    talk_btn = (Rectangle){
        dialog.x + 30,
        dialog.y + 100,
        100,
        40
    };

    quest_btn = (Rectangle){
        dialog.x + 160,
        dialog.y + 100,
        100,
        40
    };

    attack_btn = (Rectangle){
        dialog.x + 290,
        dialog.y + 100,
        100,
        40
    };

    DrawRectangleRec(
        talk_btn,
        CheckCollisionPointRec(mouse, talk_btn)
            ? GRAY
            : LIGHTGRAY
    );

    DrawRectangleRec(
        quest_btn,
        CheckCollisionPointRec(mouse, quest_btn)
            ? GRAY
            : LIGHTGRAY
    );

    DrawRectangleRec(
        attack_btn,
        CheckCollisionPointRec(mouse, attack_btn)
            ? GRAY
            : LIGHTGRAY
    );

    DrawRectangleLinesEx(talk_btn, 1, DARKGRAY);
    DrawRectangleLinesEx(quest_btn, 1, DARKGRAY);
    DrawRectangleLinesEx(attack_btn, 1, DARKGRAY);

    DrawText(
        "Talk",
        talk_btn.x + 28,
        talk_btn.y + 10,
        18,
        BLACK
    );

    DrawText(
        "Quest",
        quest_btn.x + 23,
        quest_btn.y + 10,
        18,
        BLACK
    );

    DrawText(
        "Attack",
        attack_btn.x + 18,
        attack_btn.y + 10,
        18,
        BLACK
    );

    draw_text_field(game, dialog);
}

void handle_npc_dialog(t_game *game)
{
    Rectangle dialog;
    Rectangle talk_btn;
    Rectangle quest_btn;
    Rectangle attack_btn;
    Rectangle close_btn;
    Vector2 mouse;

    dialog = get_npc_dialog();
    mouse = GetMousePosition();

    close_btn = (Rectangle){
        dialog.x + dialog.width - 40,
        dialog.y + 10,
        30,
        30
    };

    talk_btn = (Rectangle){
        dialog.x + 30,
        dialog.y + 100,
        100,
        40
    };

    quest_btn = (Rectangle){
        dialog.x + 160,
        dialog.y + 100,
        100,
        40
    };

    attack_btn = (Rectangle){
        dialog.x + 290,
        dialog.y + 100,
        100,
        40
    };

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return ;

    if (CheckCollisionPointRec(mouse, close_btn))
    {
        game->npc_open = false;
        return ;
    }

    if (CheckCollisionPointRec(mouse, talk_btn))
    {
        talk(game, game->selected_npc);
        return ;
    }

    if (CheckCollisionPointRec(mouse, quest_btn))
    {
        quest(game, game->selected_npc);
        game->npc_open = false;
        return ;
    }

    if (CheckCollisionPointRec(mouse, attack_btn))
    {
        attack(game, game->selected_npc);
        game->npc_open = false;
        return ;
    }
}
