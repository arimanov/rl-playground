#include "raylib.h"
#include <stdio.h>

int main(void) {
    InitWindow(800, 450, "Simple smth");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    float x = 400;
    float y = 225;
    float speed = 200.0f;

    while (!WindowShouldClose()) {
        // --- UPDATE ---
        float dt = GetFrameTime();
        //TraceLog(LOG_INFO, "x = %f", dt);

        if (IsKeyDown(KEY_RIGHT)) x += speed * dt;
        if (IsKeyDown(KEY_LEFT))  x -= speed * dt;
        if (IsKeyDown(KEY_DOWN))  y += speed * dt;
        if (IsKeyDown(KEY_UP))    y -= speed * dt;

        // --- DRAW ---
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(x - 25, y - 25, 50, 50, MAROON);
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}