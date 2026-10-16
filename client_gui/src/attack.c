#include "attack.h"
#include "client.h"
#include "hp.h"
#include "notification.h"
#include <stdio.h>

int parse_attack_response(const char *response, int *attacker_hp, int *target_hp, int *damage)
{
    if (extract_json_int(response, "\"attacker_hp\"", attacker_hp) < 0)
        return (-1);
    if (extract_json_int(response, "\"target_hp\"", target_hp) < 0)
        return (-1);
    if (extract_json_int(response, "\"damage\"", damage) < 0)
        return (-1);
    return (0);
}

void attack_state(t_game *game, char *buf)
{
    int attacker_hp;
    int target_hp;
    int damage;
    char notification[256];

    if (parse_attack_response(buf, &attacker_hp, &target_hp, &damage) < 0)
    {
        show_notification(game, "Failed to attack.");
        return ;
    }

    game->hp = attacker_hp;
    snprintf(notification, sizeof(notification), "Dealt %d damage. Enemy HP: %d", damage, target_hp);
    show_notification(game, notification);
    if (target_hp <= 0)
    {
        if (client_send(game->manager->client, "LOOK\n") < 0)
            return ;
        game->state = GAME_WAIT_LOOK;
        return ;
    }
    game->state = GAME_IDLE;
}
