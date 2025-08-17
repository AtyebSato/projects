#include <raylib.h>
#include <vector>
using namespace std;

Vector2 gridtopos(int row, int col, Vector2 screensize, int gridSize)
{
    float cellSizeX = screensize.x / gridSize;
    float cellSizeY = screensize.y / gridSize;

    Vector2 position;
    position.x = col * cellSizeX;
    position.y = row * cellSizeY;

    return position;
}

int main()
{
    const int screenSize = 800;
    const int gridSize = 20;
    const int cellSize = screenSize / gridSize;

    InitWindow(screenSize, screenSize, "SNAAAAAAKE");
    SetTargetFPS(60);

    struct Player {
        int row;
        int col;
        Vector2 size;
    };

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    float timer = 0;
    float deltatime = GetFrameTime();

    struct Fruit{
        int col;
        int row;
        bool active;
    };
    
    float gamespeed = 0.1;

    Player snake = {10, 10, {(float)cellSize, (float)cellSize}};
    Fruit apple = {0,0,true};

    int size = 1;
    while (!WindowShouldClose())
    {
        Vector2 playerpos = gridtopos(snake.row, snake.col, {800, 800}, gridSize);
        Vector2 applepos = gridtopos(apple.row, apple.col, {800, 800}, gridSize);
        Rectangle snakerec = {playerpos.x, playerpos.y, 40, 40};
        Rectangle applerec = {applepos.x, applepos.y, 40,40};
        timer += deltatime;
        deltatime = GetFrameTime();
        if(IsKeyPressed(KEY_RIGHT)) 
        {
            right = true;
            left = false;
            up = false;
            down = false;
        }
        if(IsKeyPressed(KEY_LEFT)) 
        {
            left = true;
            right = false;
            up = false;
            down = false;
        }
        if(IsKeyPressed(KEY_UP))
        {
            up = true;
            right = false;
            left = false;
            down = false;
        }
        if(IsKeyPressed(KEY_DOWN)) 
        {
            down = true;
            up = false;
            right = false;
            left = false;
        }
        if(right && timer >= gamespeed && snake.col < 19) {
            snake.col++;
            timer = 0;
        }
        if(left && timer >= gamespeed && snake.col > 0) {
            snake.col--;
            timer = 0;
        }
        if(up && timer >= gamespeed && snake.row > 0) {
            snake.row--;
            timer = 0;
        }
        if(down && timer >= gamespeed && snake.row < 19) {
            snake.row++;
            timer = 0;
        }


        if(CheckCollisionRecs(snakerec, applerec))
        {
            apple.col = GetRandomValue(0, 19);
            apple.row = GetRandomValue(0, 19);    
            size++;        
        }
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw snake
        DrawRectangleV(gridtopos(snake.row, snake.col, {800, 800}, gridSize), snake.size, WHITE);

        // Draw grid
        for (int y = 0; y < gridSize; y++) {
            for (int x = 0; x < gridSize; x++) {
                DrawRectangleLines(x * cellSize, y * cellSize, cellSize, cellSize, DARKGRAY);
            }
        }
        for(int i; i < size; i++)
        {
            if(right) DrawRectangle(snakerec.x - snakerec.width, snakerec.y, snakerec.width, snakerec.height, WHITE);
            if(left) DrawRectangle(snakerec.x + snakerec.width, snakerec.y, snakerec.width, snakerec.height, WHITE);
            if(up) DrawRectangle(snakerec.x, snakerec.y - snakerec.height * 2, snakerec.width, snakerec.height, WHITE);
            if(down) DrawRectangle(snakerec.x, snakerec.y + snakerec.height, snakerec.width, snakerec.height, WHITE);

        }
        DrawText(TextFormat("cols: %i", snake.col), 100, 50, 20, RED);
        DrawText(TextFormat("rows: %i", snake.row), 100, 80, 20, RED);
        DrawRectangleV(gridtopos(apple.row, apple.col, {800, 800}, gridSize), {40,40}, RED);
        if(apple.active)
        {
            DrawText("apple active", 100, 100, 20, RED);
        }
        else if(!apple.active)
        {
            DrawText("apple not active", 100, 100, 20, RED);
        }
        EndDrawing();
    }

    CloseWindow();
}
