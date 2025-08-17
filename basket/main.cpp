#include <raylib.h>
#include <vector>
using namespace std;
int main()
{
    InitWindow(800, 800, "fruit basket");
    SetTargetFPS(60);

    Rectangle player {400, 770, 30 ,30};
    int playerspeed = 6;

    struct Fruit {
        Vector2 position;
        float size;
        bool active = true;
        int speed;
    };
    
    vector <Fruit> fruits;
    vector <int> strikes; 
    float deltatime = GetFrameTime();
    float timer = 0;

    int score = 0;
    int best = 0;
    int lives = 3;

    bool alive = true;
    
    int gamescore = 0;
    while(!WindowShouldClose())
    {
        float deltatime = GetFrameTime();
        timer += deltatime;
        if(IsKeyDown(KEY_RIGHT) && player.x < 770 ) player.x += playerspeed;
        if(IsKeyDown(KEY_LEFT) && player.x > 0) player.x -= playerspeed;

        if(timer >= 1)
        {      
            
            Fruit fruit{(float)GetRandomValue(10, 790), 0, 10, true, (GetRandomValue(100, 250))};
            fruits.push_back(fruit);
            timer = 0;
        }

        for(Fruit& f : fruits)
        {
            if(CheckCollisionCircleRec(f.position, 10, player) && f.active == true && alive == true)
                {
                     f.active = false;
                     score += 1;
                }
            f.position.y += f.speed * deltatime; // falling speed
            if(f.position.y >= 800 && f.active == true)
            {
                f.active = false;
                lives--;
            }
        }

        if (lives == 0)
            {
                alive = false;
                if (score > best) 
                {
                best = score;
                }
                gamescore = score;
            }   
        
        if(IsKeyPressed(KEY_SPACE) && alive == false)
        {
            alive = true;
            lives = 3;
            score = 0;
        }
        BeginDrawing();

        ClearBackground(BLACK);

        if(alive == true)
        {
            DrawRectangleRec(player, WHITE);
            DrawText(TextFormat("score: %i", score), 100, 30, 20, WHITE);

            for (const Fruit& f : fruits)
            {
                 if(f.active == true)
                    {
                        DrawCircleV(f.position, 10, RED);
                    }          
            }
        } 

        if(!alive) 
        {
            fruits.clear();
            gamescore = score;
            DrawText("GAME\nOVER", 200, 300 , 100, WHITE);
            DrawText("press SPACE to restart", 200, 600, 30, WHITE);
            if(gamescore == best && best > 0)
            {
                DrawText(TextFormat("New record: %i", best), 250, 650 , 30, WHITE);
            }
        }
        DrawText(TextFormat("best score: %i", best), 100, 50, 20, WHITE);

        EndDrawing();
    }
    CloseWindow();
}
