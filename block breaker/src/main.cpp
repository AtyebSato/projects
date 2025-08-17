#include <mutex>
#include <raylib.h>

int main()
{
    InitWindow(1280, 720, "block breaker");
    SetTargetFPS(60);

    Rectangle player = {540, 680, 200, 10};
    Vector2 ball = {640, 360};
    Vector2 velo = {0, 10};

    const int rows = 5;
    const int cols = 10;
    const int blockWidth = 100;
    const int blockHeight = 30;
    const int spacing = 10;  
    const int startY = 50;
    const int startX = 80;

    Rectangle blocks[rows * cols];
    bool alive[rows * cols];

    // Initialize blocks and alive status once before the game loop
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int i = r * cols + c;
            blocks[i].x = startX + c * (blockWidth + spacing);
            blocks[i].y = startY + r * (blockHeight + spacing);
            blocks[i].width = blockWidth;
            blocks[i].height = blockHeight;
            alive[i] = true;
        }
    }

    while (!WindowShouldClose())
    {
        // Move the ball
        ball.x += velo.x;
        ball.y += velo.y;

        // Player movement
        if (IsKeyDown(KEY_RIGHT) && player.x + player.width < 1280)
            player.x += 10;
        if (IsKeyDown(KEY_LEFT) && player.x > 0)
            player.x -= 10;

        // Ball collision with player paddle
        if (CheckCollisionCircleRec(ball, 10, player))
        {
            float playercenter = player.x + player.width / 2;
            float relativeX = (ball.x - playercenter) / (player.width / 2);
            velo.y = -velo.y;
            velo.x = relativeX * 10;
        }

        // Ball collision with blocks
        for (int i = 0; i < rows * cols; i++)
        {
            if (alive[i] && CheckCollisionCircleRec(ball, 10, blocks[i]))
            {
                alive[i] = false;
                velo.y = -velo.y;  
                break;  
            }
        }

        if (ball.x + 10 >= 1280 || ball.x + 10 <= 0)
        {
            velo.x = -velo.x;
        }


        bool alldestryoed = true;
        for (int i = 0; i < 50; i++)
        {
            if (alive[i])
            {
                alldestryoed = false;
                break;
            }
            
        }
        if (alldestryoed)
        {
            ball.x = 640;
            ball.y = 360;
            velo.x = 0;
            velo.y = 10;

        for (int i = 0; i < 50; i++) 
        {
        alive[i] = true;
        }
        }
        
        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleRec(player, WHITE);

        for (int i = 0; i < rows * cols; i++)
        {
            if (alive[i])
                DrawRectangleRec(blocks[i], WHITE);
        }

        DrawCircleV(ball, 10, WHITE);
        EndDrawing();
    }

    CloseWindow();
}
