#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include "login.h"
#include "client.h"
#include "game.h"

void handle_username_input(t_login *login)
{
    int key;

    key = GetCharPressed();

    while (key > 0)
    {
        if (key >= 32 && key <= 126 && login->username_len < 63)
        {
            login->username[login->username_len++] = (char)key;
            login->username[login->username_len] = '\0';
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && login->username_len > 0)
    {
        login->username_len--;
        login->username[login->username_len] = '\0';
    }

    const int button_width = 120;
    const int button_height = 40;

    int input_y = (GetScreenHeight() - 40) / 2 - 30;

    Rectangle button = {
        (GetScreenWidth() - button_width) / 2,
        input_y + 40 + 20,
        button_width,
        button_height
    };
}

static void login_submit(t_login *login)
{
    if (login->username_len == 0)
        return ;

    if (client_connect(
            login->manager->client,
            "127.0.0.1",
            4242
        ) < 0)
    {
        login->state = LOGIN_ERROR;
        strcpy(login->error, "Could not connect to server");
        return ;
    }

    login->state = LOGIN_WAIT_HELLO;
}

static void login_draw(t_scene *scene)
{
    t_login *login = (t_login *)scene;

    const int input_width = 300;
    const int input_height = 40;
    const int button_width = 120;
    const int button_height = 40;
    const int spacing = 20;

    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    int input_x = (screen_width - input_width) / 2;
    int input_y = (screen_height - input_height) / 2 - 30;

    int button_x = (screen_width - button_width) / 2;
    int button_y = input_y + input_height + spacing;

    Rectangle button = {
        button_x,
        button_y,
        button_width,
        button_height
    };

    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, button);

    ClearBackground(RAYWHITE);

    DrawRectangleLines(
        input_x,
        input_y,
        input_width,
        input_height,
        DARKGRAY
    );

    DrawText(
        login->username,
        input_x + 10,
        input_y + 10,
        20,
        BLACK
    );

    DrawRectangleRec(
        button,
        hovered ? LIGHTGRAY : GRAY
    );

    const char *button_text = "Submit";
    int text_width = MeasureText(button_text, 20);

    DrawText(
        button_text,
        button_x + (button_width - text_width) / 2,
        button_y + (button_height - 20) / 2,
        20,
        BLACK
    );
}

static void login_update(t_scene *scene)
{
    t_login *login = (t_login *)scene;
    t_client *client = login->manager->client;
    t_scene *game;
    int bytes;
    char buf[BUFFER_SIZE];
    char cmd[128];

    handle_username_input(login);

    if (login->state == LOGIN_IDLE)
    {
        if (IsKeyPressed(KEY_ENTER))
            login_submit(login);

        return ;
    }

    if (login->state == LOGIN_WAIT_HELLO)
    {
        bytes = client_receive(client, buf, sizeof(buf));
        if (bytes > 0)
        {
            if (strncmp(buf, "OK hello", 8))
            {
                login->state = LOGIN_ERROR;
                strcpy(login->error, "Invalid server handshake.");
                return ;
            }

            snprintf(cmd, sizeof(cmd), "CONNECT %s\n", login->username);
            client_send(client, cmd);

            login->state = LOGIN_WAIT_CONNECTED;
        }

        return ;
    }

    if (login->state == LOGIN_WAIT_CONNECTED)
    {
        bytes = client_receive(client, buf, sizeof(buf));
        if (bytes > 0)
        {
            if (strncmp(buf, "OK connected", 12))
            {
                login->state = LOGIN_ERROR;
                strcpy(login->error, "Server rejected connection.");
                return ;
            }
            client->connected = 1;

            if (client_send(client, "LOOK\n") < 0)
            {
                login->state = LOGIN_ERROR;
                strcpy(login->error, "Failed to send LOOK.");
                return ;
            }

            login->state = LOGIN_WAIT_LOOK;
        }

        return ;
    }

    if (login->state == LOGIN_WAIT_LOOK)
    {
        bytes = client_receive(client, buf, sizeof(buf));
        if (bytes > 0)
        {
            if (strncmp(buf, "OK ", 3))
            {
                login->state = LOGIN_ERROR;
                strcpy(login->error, "LOOK failed.");
                return ;
            }

            game = game_create(login->manager, buf + 3);
            if (game == NULL)
            {
                login->state = LOGIN_ERROR;
                strcpy(login->error, "Failed to create game scene.");
                return ;
            }

            scene_manager_set(login->manager, game);
            return ;
        }
    }

}

static void login_destroy(t_scene *scene)
{
    t_login *login = (t_login *)scene;
    free(login);
}

t_scene *login_create(t_manager *manager)
{
    t_login *login = malloc(sizeof(*login));
    if (!login)
        return NULL;

    *login = (t_login){
        .base = {
            .update = login_update,
            .draw = login_draw,
            .destroy = login_destroy
        },
        .manager = manager,
        .username = "",
        .username_len = 0,
        .input_active = 0
    };

    return (t_scene *)login;
}

