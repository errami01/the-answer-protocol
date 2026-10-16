#include <raylib.h>
#include <string.h>
#include "game.h"
#include "attack.h"
#include "client.h"
#include "game_arrows.h"
#include "game_commands.h"
#include "game_components_utils.h"
#include "game_components.h"
#include "game_utils.h"
#include "inventory.h"
#include "notification.h"
#include "npc.h"
#include "hp.h"
#include "quest.h"

static void game_update(t_scene *scene)
{
    t_game     *game;
    char buf[BUFFER_SIZE];
    int bytes;

    game = (t_game *)scene;
    if (game->current == NULL)
        return ;

    if (game->state == GAME_IDLE)
    {
        if (IsKeyPressed(KEY_I))
        {
            if (game->inventory_open)
                game->inventory_open = 0;
            else
                inventory(game);

            return ;
        }

        if (IsKeyPressed(KEY_Q))
        {
            if (game->quests_open)
                game->quests_open = 0;
            else
                quests(game);
        }

        if (game->npc_open)
        {
            handle_npc_dialog(game);
            return ;
        }

        handle_movement_buttons(game);
        handle_item_clicks(game);

        return ;
    }

    bytes = client_receive(game->manager->client, buf, sizeof(buf));
    if (bytes <= 0)
        return ;

    printf("RECEIVED: [%s]\n", buf);

    if (game->state == GAME_WAIT_MOVE)
    {
        if (strncmp(buf, "OK room=", 8) == 0)
        {
            client_send(game->manager->client, "LOOK\n");
            game->state = GAME_WAIT_LOOK;
        }

        return ;
    }

    if (game->state == GAME_WAIT_TAKE)
    {
        if (strncmp(buf, "OK taken=", 9) == 0)
        {
            client_send(game->manager->client, "LOOK\n");
            game->state = GAME_WAIT_LOOK;
        }

        return ;
    }

    if (game->state == GAME_WAIT_LOOK)
    {
        t_room *room = malloc(sizeof(*room));
        if (!room)
            return ;

        if (parse_look(buf, room) < 0)
        {
            free(room);
            return ;
        }

        free(game->current);
        game->current = room;
        game->state = GAME_IDLE;
    }

    if (game->state == GAME_WAIT_STATUS)
    {
        if (parse_status(buf, game) < 0)
            return ;
        game->state = GAME_IDLE;
    }

    if (game->state == GAME_WAIT_INVENTORY)
    {
        if (parse_inventory(buf, game) < 0)
        {
            game->state = GAME_IDLE;
            return ;
        }

        game->inventory_open = 1;
        game->state = GAME_IDLE;
        return ;
    }

    if (game->state == GAME_WAIT_QUESTS)
    {
        if (parse_quests(buf, game) < 0)
        {
            game->state = GAME_IDLE;
            return ;
        }

        game->quests_open = 1;
        game->state = GAME_IDLE;
        return ;
    }

    if (game->state == GAME_WAIT_TALK)
    {
        strncpy(game->npc_response, buf + 3, sizeof(game->npc_response) - 1);
        game->npc_response[sizeof(game->npc_response) - 1] = '\0';

        game->state = GAME_IDLE;
        return ;
    }

    if (game->state == GAME_WAIT_QUEST)
        quest_state(game, buf);

    if (game->state == GAME_WAIT_ATTACK)
        attack_state(game, buf);
}

static void game_draw(t_scene *scene)
{
    t_game *game = (t_game *)scene;

    ClearBackground(RAYWHITE);

    if (game->current == NULL)
    {
        DrawText("No room data", 20, 20, 20, RED);
        return ;
    }

    DrawText(
        TextFormat("Current Room: %s", game->current->name),
        20,
        20,
        20,
        BLACK
    );

    DrawText(
        game->current->description,
        20,
        60,
        15,
        DARKGRAY
    );

    draw_hp_bar(game);
    draw_items(game);
    draw_npcs(game);
    draw_notification(game);

    int center_x = GetScreenWidth() / 2;
    int center_y = GetScreenHeight() / 2;

    if (game->current->north[0] != '\0')
    {
        draw_arrow_up(
            center_x,
            center_y - 100,
            game->current->north
        );
    }

    if (strlen(game->current->south) > 0)
    {
        draw_arrow_down(
            center_x,
            center_y + 100,
            game->current->south
        );
    }

    if (game->current->west[0] != '\0')
    {
        draw_arrow_left(
            center_x - 150,
            center_y,
            game->current->west
        );
    }

    if (game->current->east[0] != '\0')
    {
        draw_arrow_right(
            center_x + 150,
            center_y,
            game->current->east
        );
    }

    if (game->inventory_open)
        draw_inventory(game->inventory);

    if (game->npc_open)
        draw_npc_dialog(game);

    if (game->quests_open)
        draw_quests(game);
}

static void game_destroy(t_scene *scene)
{
    t_game *game = (t_game *)scene;

    clear_inventory(game);
    if (game->current)
        free(game->current);

    free(game);
}

t_scene *game_create(t_manager *manager, const char *look_init)
{
    t_game *game = calloc(1, sizeof(*game));
    if (!game)
        return (NULL);

    game->base.update = game_update;
    game->base.draw = game_draw;
    game->base.destroy = game_destroy;

    game->manager = manager;

    t_room *room = malloc(sizeof(*room));
    if (parse_look(look_init, room) < 0)
    {
        printf("Failed to parse look.");
        return NULL;
    }

    game->current = room;
    game->npc_response[0] = '\0';

    status(game);

    printf("%d %d", game->hp, game->max_hp);

    return ((t_scene *)game);
}
