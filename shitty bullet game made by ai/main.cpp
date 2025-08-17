#include <raylib.h>
#include <vector>
#include <algorithm> 
#include <raymath.h>  
#include <iostream>

using namespace std;

struct Bullet {
    Vector2 position;
    Vector2 direction;
    float speed = 10.0f;
};

struct Enemy {
    Vector2 position;
    float height = 40;
    float width  = 40;
    float speed = 2.0f;
    bool alive;
};

Enemy Spawn(int ScreenHeight, int ScreenWidth)
{
    float enemyX = GetRandomValue(0, ScreenWidth);
    float enemyY = GetRandomValue(0, ScreenHeight); 
    return { {enemyX, enemyY}, 40.0f, 40.0f, 2.0f, true };
}

int main() {
    InitWindow(1280, 720, "Bullet hell");
    SetTargetFPS(60);

    const int playerheight = 40;
    const int playerwidth = 40;
    Vector2 playerPos = { 400 + (playerwidth / 2), 300 + (playerheight / 2) };
    Rectangle player = { playerPos.x, playerPos.y, 40, 40 };

    vector<Bullet> bullets;
    vector<Enemy> enemies;

    float timer = 0;
    float damageinvins = 0;

    int hp = 5;
    while (!WindowShouldClose()) {
        // === Input ===
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            Vector2 direction = Vector2Normalize(Vector2Subtract(mousePos, playerPos));
            bullets.push_back({ {playerPos.x + 20, playerPos.y + 20}, direction });
        }

        if (IsKeyDown(KEY_A)) playerPos.x -= 5;
        if (IsKeyDown(KEY_D)) playerPos.x += 5;
        if (IsKeyDown(KEY_W)) playerPos.y -= 5;
        if (IsKeyDown(KEY_S)) playerPos.y += 5;

        player.x = playerPos.x;
        player.y = playerPos.y;

        // === Update bullets ===
        for (auto& bullet : bullets) {
            bullet.position = Vector2Add(bullet.position, Vector2Scale(bullet.direction, bullet.speed));
        }

        // Remove off-screen bullets
        bullets.erase(
            remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {
                return (b.position.x < 0 || b.position.x > 1280 ||
                        b.position.y < 0 || b.position.y > 720);
            }),
            bullets.end()
        );

        // === Spawn enemies every 5 seconds ===
        float deltaTime = GetFrameTime();
        timer += deltaTime;
        if (timer >= 5.0f) {
            enemies.push_back(Spawn(720, 1280));
            timer = 0;
        }

        // === Move enemies toward player and check collisions ===
        for (auto& enemy : enemies) {
            if (!enemy.alive) continue;

            // Move toward player
            Vector2 direction = Vector2Normalize(Vector2Subtract(playerPos, enemy.position));
            enemy.position = Vector2Add(enemy.position, Vector2Scale(direction, enemy.speed));

            // Bullet collision
            Rectangle enemyRect = { enemy.position.x, enemy.position.y, enemy.width, enemy.height };
            for (size_t i = 0; i < bullets.size(); ++i) {
                if (CheckCollisionCircleRec(bullets[i].position, 5.0f, enemyRect)) {
                    enemy.alive = false;
                    bullets.erase(bullets.begin() + i);
                    break;
                }
            }
            if(CheckCollisionRecs(player, enemyRect))
            {
                damageinvins += deltaTime;
                if(damageinvins >= 2)
                {
                    hp--;
                    damageinvins = 0;
                }


            }
        }
        damageinvins += deltaTime;
        // === Draw everything ===
        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleRec(player, WHITE);

        for (const auto& bullet : bullets) {
            DrawCircleV(bullet.position, 5, RED);
        }

        for (const auto& enemy : enemies) {
            if (enemy.alive) {
                DrawRectangle(enemy.position.x, enemy.position.y, enemy.width, enemy.height, RED);
            }
        }

        if(hp == 5)
        {
            DrawCircle(100, 50, 10, RED);
            DrawCircle(120, 50, 10, RED);
            DrawCircle(140, 50, 10, RED);
            DrawCircle(160, 50, 10, RED);
            DrawCircle(180, 50, 10, RED);
        }
        else if(hp == 4)
        {
            DrawCircle(100, 50, 10, RED);
            DrawCircle(120, 50, 10, RED);
            DrawCircle(140, 50, 10, RED);
            DrawCircle(160, 50, 10, RED);
        }
            if(hp == 3)
        {
            DrawCircle(100, 50, 10, RED);
            DrawCircle(120, 50, 10, RED);
            DrawCircle(140, 50, 10, RED);
        }
            else if(hp == 2)
        {
            DrawCircle(100, 50, 10, RED);
            DrawCircle(120, 50, 10, RED);
        }
            else if(hp == 1)
        {
            DrawCircle(100, 50, 10, RED);
        }
        DrawText(TextFormat("%f", damageinvins), 600, 200, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
