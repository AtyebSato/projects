#include <cmath>
#include <raylib.h>
#include <raymath.h>

int main()
{
    InitWindow(1280, 720, "racists");
    SetTargetFPS(60);

    Rectangle car = {640,360,50,100};
    Vector2 direction = Vector2Subtract(GetMousePosition(),{car.x, car.y});
    float angle = atan2f(direction.y, direction.x) * RAD2DEG - 90;
    Camera2D camera;
    float rotation;
    while(!WindowShouldClose())
    {
        direction = Vector2Subtract(GetMousePosition(),{car.x, car.y});
        angle = atan2f(direction.y, direction.x) * RAD2DEG;
        if (IsKeyDown(KEY_D)) rotation += 3;
        if (IsKeyDown(KEY_A)) rotation -= 3;
        camera.rotation = rotation;
        camera.target = {car.x, car.y};
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectanglePro(car, {25,0}, angle, WHITE);
        EndDrawing();
    }
    CloseWindow();
}