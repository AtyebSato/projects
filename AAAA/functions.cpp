#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <algorithm>
#include "headers/assets.h"
#include "headers/bullet.h"
#include "headers/Enemies.h"
#include "headers/coin.h"
#include "headers/enums.h"
#include "headers/player.h"
#include "headers/globals.h"
#include "headers/raygui.h"
state currentstate = state::inmenu;
Portaltype currentPortal = Portaltype::castleport;
weapons currentweapon = weapons::pistol;


void killing(std::vector<Enemy>& enemyvec, std::vector<Bullet>& bullets, int goldchance, int diamondchance, int silverchance)
{
    for (Enemy& enemy : enemyvec)
    {
        for (Bullet& b : bullets)
        {
            if (CheckCollisionCircleRec(b.position, 10, { enemy.position.x, enemy.position.y, enemy.size.x, enemy.size.y }))
            {
                b.active = false;
                enemy.health--;
                enemy.hit = true;
                enemy.hittime = 0.0f; // Reset on every hit

                switch (GetRandomValue(1, 2))
                {
                    case 1: PlaySound(hit); break;
                    case 2: PlaySound(hit2); break;
                }
            }
        }

        if (enemy.hit)
        {
            enemy.hittime += GetFrameTime();

            if (enemy.hittime >= 0.2f)
            {
                enemy.hit = false;

                if (enemy.health <= 0)
                {
                    enemy.alive = false;
                    PlaySound(enemydeath);

                    int cointype = GetRandomValue(1, 100);

                    if (cointype <= goldchance && goldchance != 0)
                    {
                        coins.push_back(Coin(10, &coinsprite, enemy.position + enemy.size / 2));
                    }
                    else if (cointype <= goldchance + diamondchance && diamondchance != 0)
                    {
                        coins.push_back(Coin(30, &diamondsprite, enemy.position + enemy.size / 2));
                    }
                    else if (cointype <= goldchance + diamondchance + silverchance && silverchance != 0)
                    {
                        coins.push_back(Coin(5, &silversprite, enemy.position + enemy.size / 2));
                    }
                }
            }
        }
    }


    // Garbage collection happens **after** the loop
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& b) {
        return !b.active;
    }), bullets.end());

    enemyvec.erase(std::remove_if(enemyvec.begin(), enemyvec.end(), [](Enemy& e) {
        return !e.alive && !e.hit && e.hittime >= 0.2f;
    }), enemyvec.end());
}


 void charactermovment(Player& player, int speed = 300)
    {
        if (!inshop)
        {
            if(IsKeyDown(KEY_D)) player.position.x += speed * GetFrameTime();
            if(IsKeyDown(KEY_A)) player.position.x -= speed * GetFrameTime(); 
            if(IsKeyDown(KEY_W)) player.position.y -= speed * GetFrameTime(); 
            if(IsKeyDown(KEY_S)) player.position.y += speed * GetFrameTime(); 
        }
    }

    bool fireready = true;
    float firecooldown = 0;

    void shoot(std::vector<Bullet>& bulletvec, Player& player)
    {
        if(IsKeyPressed(KEY_TWO) && currentweapon == weapons::pistol) currentweapon = weapons::rifle;
        if(IsKeyPressed(KEY_ONE) && currentweapon == weapons::rifle) currentweapon = weapons::pistol;
        if(!fireready)
        {
            firecooldown += GetFrameTime();
            if(firecooldown >= 0.2)
            {
                firecooldown = 0;
                fireready = true;
            }    
        }
        if (currentweapon == weapons::pistol)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 dir = Vector2Normalize(Vector2Subtract(GetMousePosition(), player.position));
                bulletvec.push_back(Bullet((Vector2){player.position.x + player.size.x /2, player.position.y + player.size.y/2}, dir, true, 1, 5));
                switch (GetRandomValue(1, 3)) {
                    case 1: 
                    SetSoundVolume(bulletshoot, 0.5);
                    PlaySound(bulletshoot);
                    break;
                    case 2: 
                    SetSoundVolume(bulletshoot2, 0.5);                  
                    PlaySound(bulletshoot2);
                    break;
                    case 3: 
                    SetSoundVolume(bulletshoot3, 0.5);                    
                    PlaySound(bulletshoot3);
                    break;
                }
            }
            for (Bullet& b : bulletvec)
            {
                b.position += b.dir * 700 * GetFrameTime();
            }
        }
        else if (currentweapon == weapons::rifle)
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && fireready && rifleammo > 0)
            {
                fireready = false;
                rifleammo--;
                Vector2 dir = Vector2Normalize(Vector2Subtract(GetMousePosition(), player.position));
                bulletvec.push_back(Bullet((Vector2){player.position.x + player.size.x /2, player.position.y + player.size.y/2}, dir, true, 0.5,3));
                switch (GetRandomValue(1, 3)) {
                    case 1: PlaySound(bulletshoot);
                    break;
                    case 2: PlaySound(bulletshoot2);
                    break;
                    case 3: PlaySound(bulletshoot3);
                    break;
                }
            }
            for (Bullet& b : bulletvec)
            {
                b.position += b.dir * 1000 * GetFrameTime();
            }
        }
    }
    float timer = 0;
    void spawnenemies(Enemy& enemy, std::vector<Enemy>& enemiesvec, Player& player, std::vector<Bullet>& bulletvec, int maxenemies, float spawntime)
    {
        timer += GetFrameTime();
        if(timer >= spawntime && totalSpawnedEnemies <= maxenemies)
        {
            Vector2 position = {(float)GetRandomValue(0, 1280), (float)GetRandomValue(0, 720)};
            Vector2 dir = Vector2Normalize(Vector2Subtract(position, player.position));
            enemiesvec.push_back(Enemy(enemy.damage, enemy.health, enemy.speed, enemy.texture, enemy.texturehit, enemy.size, position));
            timer = 0;
            totalSpawnedEnemies++;
        }
        for (Enemy& e : enemiesvec)
        {   
            e.dir = Vector2Normalize(Vector2Subtract(player.position, e.position ));
            if (!e.hit) e.position += e.dir * GetFrameTime() * e.speed;
            if (e.health <= 0) e.alive = false;
            if(CheckCollisionRecs({player.position.x, player.position.y, player.size.x, player.size.y}, {e.position.x, e.position.y, e.size.x, e.size.y}) && !player.invincibile)
            {
                player.invincibile = true;
                player.health -= e.damage;
                PlaySound(hurt);
            }
        }
    }
void drawenemies(std::vector<Enemy>& enemyvec, Player& player)
{
    
    for (Enemy& e : enemyvec)
    {
        Vector2 enemyCenter = { e.position.x + 20, e.position.y + 20 };
        Vector2 origin = { 20, 20 };
        float angle = Vector2Angle(e.position, player.position) * RAD2DEG;

        Rectangle dest;
        Rectangle source;
        if (!e.hit)
        {
            source = { 0, 0, (float)e.texture->width, (float)e.texture->height };
            dest = { enemyCenter.x, enemyCenter.y, e.size.x, e.size.y };
            DrawTexturePro(*e.texture, source, dest, origin, angle, WHITE);
        }
        else
        {
            source = { 0, 0, (float)e.texturehit->width, (float)e.texturehit->height };
            dest = { enemyCenter.x, enemyCenter.y, e.size.x, e.size.y };
            DrawTexturePro(*e.texturehit, source, dest, origin, angle, WHITE);
        }
    }
    for(Coin c: coins)
    {
        DrawTexture(*c.sprite, c.position.x, c.position.y, WHITE);
    }
}


void DrawTextOutlined(Font font, const char* text, Vector2 pos, float fontSize, float spacing, Color outlineColor, Color textColor, int thickness)
{
    // Draw outline
    for (int dx = -thickness; dx <= thickness; dx++) {
        for (int dy = -thickness; dy <= thickness; dy++) {
            if (dx == 0 && dy == 0) continue; // Skip center
            Vector2 offset = { pos.x + dx, pos.y + dy };
            DrawTextEx(font, text, offset, fontSize, spacing, outlineColor);
        }
    }

    // Draw main text
    DrawTextEx(font, text, pos, fontSize, spacing, textColor);
}

void DrawRectWithOutline(int x, int y, int width, int height, int thickness, Color color, Color outlineColor)
{
    // Draw filled center
    DrawRectangle(x, y, width, height, color);
    // Draw outline (borders)
    DrawRectangle(x, y, width, thickness, outlineColor);                              // Top
    DrawRectangle(x, y + height - thickness, width, thickness, outlineColor);         // Bottom
    DrawRectangle(x, y, thickness, height, outlineColor);                             // Left
    DrawRectangle(x + width - thickness, y, thickness, height, outlineColor);         // Right
}




