
#include <raylib.h>
#include <vector>
#include <raymath.h>
#include <algorithm>
#include <string>
#include <iostream>
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
        float health;
        Vector2 dir = {0,0};
        Vector2 size = {20,20};
        bool alive = false;
    };

    vector <Enemy> enemies;

    struct ShopItem{
        int id;
        int price;
        char * name;
        char * description;
    };

    struct Rifle : ShopItem
    {
        float damage;
        bool bought = false;
        bool equipped = false;
    };

    Rifle rifle = {1, 1, "Rifle", "Shoot immense amounts of \n low damage bullets",0.5, false, false};
    int enemycount = enemies.size();
    int maxenemy = 5;
    int enemiesspawned = 0;
    // player attributes
    Rectangle player {400,400,40,40};

    int hp = 5;
    float invinciblity = 0;
    int money = 0;

    bool invincible = false;
    bool alive = true;



    // time shenanigans
    float spawntime = 0;
    float deltatime = GetFrameTime();

    // wave shenanigans
    int wave = 0;
    bool waveinprogress = true;
    
    float firecooldown = 0;
    bool fireready = true;
    bool pistolequppied = true;
    bool inshop = false;

    int shopitem1;
    int shopitem2;

    while(!WindowShouldClose())
    {
        deltatime = GetFrameTime();
        spawntime += deltatime;

        float mouseX = GetMouseX();
        float mouseY = GetMouseY();
        // moving 
        
        if(alive)
        {
            enemycount = enemies.size();

            if(IsKeyDown(KEY_A) && player.x > 0) player.x -= 5;
            if(IsKeyDown(KEY_W) && player.y > 0) player.y -= 5;
            if(IsKeyDown(KEY_D) && player.x < 800 - player.width) player.x += 5;
            if(IsKeyDown(KEY_S) && player.y < 720 - player.height) player.y += 5;


        // shooting
            // pistol
            if(IsKeyPressed(KEY_ONE))
            {
                pistolequppied = true;
                rifle.equipped = false;
            } 
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && pistolequppied && fireready)
            {
                Bullet b = {player.x + player.width / 2, player.y + player.height / 2, 5, 30};
                b.active = true;
                b.dir.x = mouseX - b.position.x;
                b.dir.y = mouseY - b.position.y;
                b.dir = Vector2Normalize(b.dir) * b.speed;
                bullets.push_back(b);
                fireready = false;
                firecooldown = 0;
            }
 
            if(!fireready)
            {
                firecooldown += deltatime;
            }
                
            cout << "firecooldown: \n" << firecooldown;
            if(firecooldown >= 0.25)
            {
                fireready = true;
            }
            //rifle
            if(IsKeyPressed(KEY_TWO) && rifle.bought == true)
            {
                rifle.equipped = true;
                pistolequppied = false;
            } 

            if( IsMouseButtonDown(MOUSE_BUTTON_LEFT) && rifle.equipped)
            {   
                Bullet b = {player.x + player.width / 2, player.y + player.height / 2, 5, 30};
                b.active = true;
                b.dir.x = mouseX - b.position.x;
                b.dir.y = mouseY - b.position.y;
                b.dir = Vector2Normalize(b.dir) * b.speed;
                bullets.push_back(b);
            }
        // enemy shenanigans

            if(spawntime >= 1 && enemycount < maxenemy && waveinprogress && enemiesspawned <= maxenemy)
            {
                Enemy e = {(float)GetRandomValue(10, 790),(float)GetRandomValue(10, 710), 10, 1};
                e.alive = true;
                enemies.push_back(e);
                spawntime = 0;
                enemiesspawned++;
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
            if(enemycount == 0 && spawntime >= 1)
            {
                waveinprogress = false;
            }
            if(enemycount == 0 && waveinprogress && spawntime >= 1)
            {
                wave++;
                waveinprogress = false;
            }
            if(!waveinprogress)
            {   
                inshop = true;
            }

            if(inshop)
            {
                if(CheckCollisionRecs(player, {100,300,200,200}) && IsKeyPressed(KEY_SPACE))
                {
                    if(shopitem1 == 1 && money >= rifle.price)
                    {
                        money -= rifle.price;
                        rifle.bought = true;
                        inshop = false;
                        waveinprogress = true;
                        enemiesspawned = 0;
                    }
                }
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
                if(e.health == 0)
                {
                    money++;
                }
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
                    e.health -= rifle.damage;
                    b.active = false;
                }
            }
        }

        if(alive)
        {
            DrawRectangleRec(player, WHITE);
            DrawText(TextFormat("Health: %i", hp), 100, 30, 20, WHITE);
            if(invincible) DrawRectangle(player.x, player.y, player.width, player.height, GRAY);
            DrawText(TextFormat("Wave: %i", wave), 100, 50, 20, WHITE);
            DrawText(TextFormat("Money: %i", money), 100, 90, 20, WHITE);        EndDrawing();
        }     

        if(!alive)
        {
            DrawText("GAME\nOVER", 300, 240, 100, WHITE); 
            DrawText("Press SPACE to Restart", 300, 350, 20, WHITE);
        } 
        enemies.erase(remove_if(enemies.begin(), enemies.end(), [](Enemy& e){ return !e.alive; }), enemies.end());
        DrawText(TextFormat("max enemies: %i", maxenemy), 100, 70, 20, WHITE);
        if(inshop)
        {
            DrawText("inshop = true", 100, 110, 20, WHITE);
        }
        else if(!inshop) {
             DrawText("inshop = false", 100, 110, 20, WHITE);
        }


        if(inshop)
        {
            shopitem1 = 1;
            
            DrawRectangle(100, 300, 200, 200, WHITE);
            if(CheckCollisionRecs(player, {100,300,200,200}))
            {
                DrawRectangle(100, 300, 200, 200, GREEN);
            }
            if(shopitem1 == rifle.id)
            {
                DrawText(rifle.name, 175, 350, 30, PURPLE);
                DrawText(rifle.description, 150, 380, 5, PURPLE);
                DrawText(TextFormat("Price: %i", rifle.price), 175, 450, 20, PURPLE);

            }
            DrawText("choose one",400 , 100, 20, WHITE);
        }
        
        DrawText(TextFormat("enemy count: %i",enemycount), 100, 130, 20, WHITE);
    }
    CloseWindow();
}