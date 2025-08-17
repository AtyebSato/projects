#include <cstdio>
#include <raylib.h>

int main()
{
    InitWindow(800, 800, "flappy bird");
    SetTargetFPS(60);
    Rectangle player {200,360,25,25};
    

    class Pipe{
        public: float x;
        public: float y;
        public: float width;
        public: float height;

        public: Pipe(float x, float y,float width,float height) {
            this->x = x;
            this->y = y;
            this->height = height;
            this->width = width;
        }
    };

    Pipe pipe31 (20, 30, 50 ,60);

    Pipe pipe1  (900,  0,50,(float)(GetRandomValue(100, 600)));
    Rectangle pipe1hb = {pipe1.x + 50,pipe1.y + pipe1.height + 200, 1 ,1};
    Pipe pipe2  (900,  pipe1.height + 200, 50 ,600);
    Pipe pipe3 (1200, 0,50,(float)GetRandomValue(100, 600));
    Rectangle pipe3hb {pipe3.x + 50,pipe3.y + pipe3.height + 200, 1 ,1};
    Pipe pipe4  (1200, pipe3.height + 200, 50 , 600);
    Pipe pipe5 (1500, 0,50, (float)GetRandomValue(50, 600));
    Rectangle pipe5hb {pipe5.x + 50,pipe5.y + pipe5.height + 200, 1 ,1};
    Pipe pipe6  (1500, pipe5.height + 200, 50, 600);

    int score = 0;
    float playervelo = 0;
    float gravity = 0.5;
    while(!WindowShouldClose())
    {
        printf("you dumb as hell");
        pipe2.y = pipe1.height + 200;
        pipe2.x = pipe1.x;

        pipe4.y = pipe3.height + 200;
        pipe4.x = pipe3.x;

        pipe6.y = pipe5.height + 200;
        pipe6.x = pipe5.x;

        pipe1.x -= 3;
        pipe1hb.x = pipe1.x + 50;
        pipe1hb.y = pipe1.y + pipe1.height + 200;

        pipe3.x -= 3;
        pipe3hb.x = pipe3.x + 50;
        pipe3hb.y = pipe3.y + pipe3.height + 200;
        
        pipe5.x -= 3;
        pipe5hb.x = pipe5.x + 50;
        pipe5hb.y = pipe5.y + pipe5.height + 200;
        // why are you reading my code bleh
        player.y += playervelo;
        playervelo += gravity;

        if(pipe1.x + 50 <= 0)
        {
            pipe1.x = 900;
            pipe1.height = GetRandomValue(50, 600);
        }
        if(pipe3.x + 50 <= 0)
        {
            pipe3.x = pipe1.x + 300;
            pipe3.height = GetRandomValue(50, 600);
        }
        if(pipe5.x + 50 <= 0)
        {
            pipe5.x = pipe3.x + 300;
            pipe5.height = GetRandomValue(50, 600);
        }
        // this is just some nerdy stuff no need to look around
        if(player.x == pipe1hb.x || player.x == pipe3hb.x || player.x == pipe5hb.x) score++;
        if(IsKeyPressed(KEY_UP))
        {
            playervelo = -10;
        }

        if(CheckCollisionRecs(player, {pipe1.x, pipe1.y, pipe1.width,pipe1.height}) || CheckCollisionRecs(player, {pipe3.x, pipe3.y, pipe3.width,pipe3.height}) ||CheckCollisionRecs(player, {pipe5.x, pipe5.y, pipe5.width,pipe1.height}) || CheckCollisionRecs(player, {pipe1.x, pipe1.y, pipe1.width,pipe1.height}) || CheckCollisionRecs(player, {pipe3.x, pipe3.y, pipe3.width,pipe3.height}) ||CheckCollisionRecs(player, {pipe5.x, pipe5.y, pipe5.width,pipe1.height}) || CheckCollisionRecs(player, {pipe2.x, pipe2.y, pipe2.width,pipe2.height}) || CheckCollisionRecs(player, {pipe4.x, pipe4.y, pipe4.width,pipe4.height}) || CheckCollisionRecs(player, {pipe6.x, pipe6.y, pipe6.width,pipe6.height}))
        {
            score = 0;
            player.x = 200;
            player.y = 360;
            pipe1.x = 900;
            pipe3.x = 1200;
            pipe5.x = 1500;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(pipe1.x, 0, 50, pipe1.height, GREEN);
        DrawRectangle(pipe2.x, pipe2.y, 50, pipe2.height, GREEN);

        DrawRectangle(pipe3.x, 0, 50, pipe3.height, GREEN);
        DrawRectangle(pipe4.x, pipe4.y, 50, pipe4.height, GREEN);

        DrawRectangle(pipe5.x, 0, 50, pipe5.height, GREEN);
        DrawRectangle(pipe6.x, pipe6.y, 50, pipe6.height, GREEN);
        
        DrawText(TextFormat("Score: %i", score), 100, 100, 20, WHITE);

        DrawRectangleRec(player, WHITE);
        EndDrawing();       
    }
    CloseWindow();
}