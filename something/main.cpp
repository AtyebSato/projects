#include <raylib.h>
#include <cmath>
int main()
{
    InitWindow(800, 800, "gravity type shit");
    SetTargetFPS(60);

    Rectangle player {400,160,40,40};
    while(!WindowShouldClose())
    {

        if(IsKeyDown(KEY_RIGHT)) player.x += 3;
        player.y = std::pow(player.x, 2) + std::sqrt(200);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircle(400, 400, 200, WHITE);
        DrawRectangleRec(player, WHITE);
        EndDrawing();
    }
    CloseWindow();
}