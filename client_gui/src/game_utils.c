#include "game_utils.h"

int extract_json_string(const char *json, const char *key, char *dst, size_t dst_size)
{
    const char  *pos;
    const char  *start;
    const char  *end;
    size_t      len;

    pos = strstr(json, key);
    if (pos == NULL)
        return (-1);

    pos += strlen(key);

    pos = strchr(pos, ':');
    if (pos == NULL)
        return (-1);

    pos++;

    while (*pos == ' ' || *pos == '\t')
        pos++;

    if (*pos != '"')
        return (-1);

    start = ++pos;

    end = strchr(start, '"');
    if (end == NULL)
        return (-1);

    len = end - start;

    if (len >= dst_size)
        len = dst_size - 1;

    memcpy(dst, start, len);
    dst[len] = '\0';

    return (0);
}

static int extract_string_array(const char *json, const char *key, char values[][128], int max_values)
{
    const char  *pos;
    const char  *start;
    const char  *end;
    size_t      len;
    int         count;

    pos = strstr(json, key);
    if (pos == NULL)
        return (0);

    pos = strchr(pos, '[');
    if (pos == NULL)
        return (-1);

    pos++;
    count = 0;

    while (*pos && *pos != ']' && count < max_values)
    {
        while (*pos == ' ' || *pos == '\t' || *pos == ',')
            pos++;

        if (*pos == ']')
            break ;

        if (*pos != '"')
            return (-1);

        start = ++pos;
        end = strchr(start, '"');

        if (end == NULL)
            return (-1);

        len = end - start;

        if (len >= 128)
            len = 127;

        memcpy(values[count], start, len);
        values[count][len] = '\0';

        count++;
        pos = end + 1;
    }

    return (count);
}

static int parse_items(const char *response, t_room *room)
{
    room->item_count = extract_string_array(response, "\"items\"", room->items, 32);
    if (room->item_count < 0)
        return (-1);

    return (0);
}

static int parse_npcs(const char *response, t_room *room)
{
    room->npc_count = extract_string_array(response, "\"npcs\"", room->npcs, 32);
    if (room->npc_count < 0)
        return (-1);

    return (0);
}

int parse_look(const char *response, t_room *room)
{
    const char *exits;

    if (response == NULL || room == NULL)
        return (-1);

    memset(room, 0, sizeof(*room));

   if (strncmp(response, "OK ", 3) == 0)
        response += 3;

    if (extract_json_string(
            response,
            "\"name\"",
            room->name,
            sizeof(room->name)) < 0)
        return (-1);

    if (extract_json_string(
            response,
            "\"description\"",
            room->description,
            sizeof(room->description)) < 0)
        return (-1);

    exits = strstr(response, "\"exits\"");
    if (exits == NULL)
        return (0);

    extract_json_string(
        exits,
        "\"north\"",
        room->north,
        sizeof(room->north));

    extract_json_string(
        exits,
        "\"south\"",
        room->south,
        sizeof(room->south));

    extract_json_string(
        exits,
        "\"east\"",
        room->east,
        sizeof(room->east));

    extract_json_string(
        exits,
        "\"west\"",
        room->west,
        sizeof(room->west));

    if (parse_items(response, room) < 0 || parse_npcs(response, room) < 0)
        return (-1);

    return (0);

}
