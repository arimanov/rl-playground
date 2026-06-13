#include "raylib.h"
#include <stdio.h>

int main(void) {
    InitWindow(800, 450, "Simple smth");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    Rectangle player = { 400, 225, 50, 50 };
    Rectangle obstacle = { 300, 200, 80, 80 };

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (IsKeyDown(KEY_RIGHT)) player.x += 200.0f * dt;
        if (IsKeyDown(KEY_LEFT))  player.x -= 200.0f * dt;
        if (IsKeyDown(KEY_DOWN))  player.y += 200.0f * dt;
        if (IsKeyDown(KEY_UP))    player.y -= 200.0f * dt;

        bool hit = CheckCollisionRecs(player, obstacle);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangleRec(obstacle, DARKGRAY);
            DrawRectangleRec(player, hit ? RED : MAROON);
            DrawText(hit ? "HIT!" : "no collision", 10, 10, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}