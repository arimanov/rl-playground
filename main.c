#include "raylib.h"
#include <stdio.h>

int main(void) {
    InitWindow(800, 450, "Simple smth");
    InitAudioDevice();
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    Texture2D robocat = LoadTexture("img.png");
    Sound jumpSound = LoadSound("resources/jump.wav");
    Sound landSound = LoadSound("resources/throw.wav");
    Music bgMusic = LoadMusicStream("resources/meadow_run.mp3");
    
    PlayMusicStream(bgMusic);

    Rectangle player = { 400, 300, 50, 50 };
    Rectangle obstacle = { 300, 200, 80, 80 };

    float velocityY = 0.0f;
    float gravity = 1000.0f;
    float jumpForce = -600.0f;
    bool isGrounded = false;
    float groundY = 350.0f;

    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.x, player.y };
    camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    bool bgtest = false;
    bool wasGrounded = true; 

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        UpdateMusicStream(bgMusic);

        if (IsKeyDown(KEY_RIGHT)) player.x += 200.0f * dt;
        if (IsKeyDown(KEY_LEFT))  player.x -= 200.0f * dt;

        velocityY += gravity * dt;

        if (IsKeyPressed(KEY_SPACE) && isGrounded) {
            velocityY = jumpForce;
            PlaySound(jumpSound);
        }

        if (IsKeyDown(KEY_B)) {
            bgtest = !bgtest;
        }

        player.y += velocityY * dt;

        if (player.y >= groundY) {
            player.y = groundY;
            velocityY = 0;
            isGrounded = true;
        } else {
            isGrounded = false;
        }

        if (isGrounded && !wasGrounded) {
            PlaySound(landSound);
        }

        bool hit = CheckCollisionRecs(player, obstacle);

        // камера следует за игроком
        camera.target = (Vector2){ player.x, player.y };
        camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };

        wasGrounded = isGrounded;

        BeginDrawing();
            if (bgtest) {
                ClearBackground(YELLOW);
            } else {
                ClearBackground(WHITE);
            }
    

            BeginMode2D(camera);
                DrawLine(-2000, groundY + 50, 2000, groundY + 50, BLACK);
                DrawRectangleRec(obstacle, DARKGRAY);

                DrawTexturePro(
                    robocat,
                    (Rectangle){ 0, 0, robocat.width, robocat.height },
                    player,
                    (Vector2){ 0, 0 },
                    0.0f,
                    hit ? RED : WHITE
                );
            EndMode2D();

            // UI рисуем СНАРУЖИ BeginMode2D — остаётся на месте на экране
            DrawText(hit ? "HIT!" : "no collision", 10, 10, 20, BLACK);
            DrawText(TextFormat("Current coord: x: %.3f; y: %.3f", player.x, player.y), 10, 30, 14, VIOLET);
            DrawText(TextFormat("BG: %d", bgtest), 10, 50, 14, VIOLET);
        EndDrawing();
    }

    
    UnloadSound(jumpSound);
    UnloadMusicStream(bgMusic);
    CloseAudioDevice();
    UnloadTexture(robocat);
    CloseWindow();
    return 0;
}