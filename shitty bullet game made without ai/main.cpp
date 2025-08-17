#include <raylib.h>
#include <vector>
#include <raymath.h>
using namespace std;
int main()
{


    InitWindow(800, 720, "neobullet");
    SetTargetFPS(60);

    struct Bullet{
        Vector2 position;
        float size;
        float speed;
        Vector2 dir = {0,0}; 
        bool active = false; 
    };

    vector <Bullet> bullets;

    struct Enemy{
        Vector2 position;
        float speed;
        int health;
        Vector2 dir = {0,0};
        Vector2 size = {20,20};
        bool alive = false;
    };

    vector <Enemy> enemies;

    int enemycount = 0;
    int maxenemy = 5;
    // player attributes
    Rectangle player {400,400,40,40};

    int hp = 5;
    float invinciblity = 0;

    bool invincible = false;
    bool alive = true;



    // time shenanigans
    float spawntime = 0;
    float deltatime = GetFrameTime();

    // wave shenanigans
    int wave = 0;
    bool waveinprogress = true;
    int killedinwave = 0;
    
    float firecooldown = 0;
     bool fireready = true;

    while(!WindowShouldClose())
    {
        deltatime = GetFrameTime();
        spawntime += deltatime;

        float mouseX = GetMouseX();
        float mouseY = GetMouseY();
        // moving 
        if(alive)
        {
            
            if(IsKeyDown(KEY_A) && player.x > 0) player.x -= 5;
            if(IsKeyDown(KEY_W) && player.y > 0) player.y -= 5;
            if(IsKeyDown(KEY_D) && player.x < 800 - player.width) player.x += 5;
            if(IsKeyDown(KEY_S) && player.y < 720 - player.height) player.y += 5;


        // shooting

            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Bullet b = {player.x + player.width / 2, player.y + player.height / 2, 5, 30};
                b.active = true;
                b.dir.x = mouseX - b.position.x;
                b.dir.y = mouseY - b.position.y;
                b.dir = Vector2Normalize(b.dir) * b.speed;
                bullets.push_back(b);
            }
        
        // enemy shenanigans

            if(spawntime >= 1 && enemycount < maxenemy && waveinprogress)
            {
                Enemy e = {(float)GetRandomValue(10, 790),(float)GetRandomValue(10, 710), 10, 5};
                e.alive = true;
                enemies.push_back(e);
                spawntime = 0;
                enemycount++;
            }
        
            if(invincible)
            {
                invinciblity += deltatime;
                if(invinciblity >= 1.5)
                {
                    invincible = false;
                    invinciblity = 0;
                }
            }

            if(killedinwave >= maxenemy && waveinprogress)
            {
                wave++;
                maxenemy += 5;
                waveinprogress = false;
                killedinwave = 0;
            }

        }
        if(hp <= 0) alive = false;
        BeginDrawing();
        ClearBackground(BLACK);
        for(Bullet& b : bullets)
        {
            if(b.active && alive)
            {
                b.position.x += b.dir.x;
                b.position.y += b.dir.y;
                DrawCircleV(b.position, b.size, RED);
                if (b.position.x > 800 || b.position.x < 0|| b.position.y < 0 || b.position.y > 720)
                {
                    b.active = false;
                }
            }
        }
        for(Enemy& e : enemies)
        {
            if(e.alive && alive )
            {

                Vector2 edir {player.x + player.width / 2 - e.position.x, player.y + player.height / 2 - e.position.y};
                e.dir = Vector2Normalize(edir);
                e.position.x += e.dir.x;
                e.position.y += e.dir.y;
                DrawRectangleV(e.position, e.size, RED);
            }
            if(CheckCollisionRecs(player, {e.position.x, e.position.y, e.size.x, e.size.y}) && !invincible && e.alive && alive)
            {
                hp--;
                invincible = true;
            }
            if(e.health <= 0) e.alive = false;
        }
        for(Enemy& e : enemies)
        {
            for(Bullet& b : bullets)
            {
                Rectangle b1 = {e.position.x, e.position.y, e.size.x, e.size.y};
                if(CheckCollisionCircleRec(b.position, b.size, b1) && e.alive && b.active)
                {
                    e.health--;
                    b.active = false;
                    enemycount--;
                    killedinwave++;
                }
            }
        }

        if(alive)
        {
            DrawRectangleRec(player, WHITE);
            DrawText(TextFormat("Health: %i", hp), 100, 30, 20, WHITE);
            if(invincible) DrawRectangle(player.x, player.y, player.width, player.height, GRAY);
            DrawText(TextFormat("Wave: %i", wave), 100, 50, 20, WHITE);
        }     

        if(!alive)
        {
            DrawText("GAME\nOVER", 300, 240, 100, WHITE); 
            DrawText("Press SPACE to Restart", 300, 350, 20, WHITE);
        } 
        DrawText(TextFormat("max enemies: %i", maxenemy), 100, 70, 20, WHITE);
        EndDrawing();
    }
    CloseWindow();
}