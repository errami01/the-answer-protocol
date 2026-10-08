#include <raylib.h>
#include "client.h"
#include "login.h"

int main(void)
{
    t_scene *scene;
    t_manager manager;
    t_client client;

    InitWindow(1200, 800, "My Raylib Game");
    SetTargetFPS(60);

    client_init(&client);
    scene_manager_init(&manager, &client);
    scene = login_create(&manager);
    if (!scene)
    {
        CloseWindow();
        return (1);
    }
    scene_manager_set(&manager, scene);
    while (!WindowShouldClose())
    {
        scene_manager_update(&manager);
        BeginDrawing();
        scene_manager_draw(&manager);
        EndDrawing();
    }
    scene_manager_destroy(&manager);
    client_disconnect(&client);
    CloseWindow();
    return (0);
}
