#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "headers/logic.h"
#include "headers/Enemies.h"
#include "headers/assets.h"
#include "headers/coin.h"
#include "headers/player.h"
#include "headers/functions.h"
#include "headers/bullet.h"
#include "headers/enums.h"
#include "headers/globals.h"
int spawned_enemies = 0;
void spawnportals(std::vector <Portal>& portals)
{
    for (int i = 0; i < 5; )
    {
        Vector2 position;
        position.x = GetRandomValue(0, 1280 - portal.width);
        position.y = GetRandomValue(0, 720 - portal.height);

        bool tooClose = false;
        for (const Portal& existing : portals)
        {
            if (Vector2Distance(position, existing.position) < 200)
            {
                tooClose = true;
                break;
            }
        }

        if (!tooClose)
        {
            enum Portaltype type = (GetRandomValue(0, 1) == 0) ? Portaltype::red : Portaltype::castleport;
            portals.push_back({position, false, true, type});
            i++; // Only increment when a valid portal is added
        }
    }
}
void castleportlogic(std::vector<Bullet>& bullets,Player& player)
{   
        charactermovment(player);
        spawnenemies(cg, enemies, player, bullets, 3, 3);
        coinlogic(player);
        shoot(bullets, player);
        wavelogic(player, bullets);
        if (player.invincibile && currentstate == state::inwave)player.invincibilty += GetFrameTime();

         if (player.invincibilty >= 3 && currentstate == state::inwave)
        {
            player.invincibile = false;
            player.invincibilty = 0;
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            player.health = 0;
            currentstate = state::indeath;
        }

        if (IsKeyPressed(KEY_F9) && player.debug) 
        {
            currentstate = state::inworld;
        }
}
void worldlogic(Player& player)
{
    charactermovment(player);

    for(int i = 0; i < portals.size() ;i++)
    {
        portals[i].selected = false;
        if (std::sqrt(std::pow(((player.position.x + 20) - (portals[i].position.x + 30)), 2) + std::pow(((player.position.y + 20) - (portals[i].position.y + 50)), 2)) <= 100)
        {
            portals[i].selected = true;
            if (portals[i].selected == true && currentstate == state::inworld && IsKeyPressed(KEY_F) && inshop == false)
            {
                currentstate = state::inwave;
                loading = true;
                currentPortal = portals[i].portaltype;
                portals.erase(portals.begin() + i);
                std::cout << "portal pressed";
            }
            break;
        }
    }
}
void deathlogic(Player& player)
{
        
    bullets.clear();
    castleguards.clear();
    magmas.clear();
    portals.clear();
    player.invincibile = false;
    player.invincibilty = 0;
    timer = 0;
    player.position.x = 640;
    player.position.y = 360;
    if (IsKeyPressed(KEY_SPACE))
    {
        player.alive = true;
        player.health = 3;
        currentstate = state::inmenu;
        spawnportals(portals);
    }
}
void redportlogic(std::vector<Bullet>& bullets, Player& player)
{
        charactermovment(player);
        shoot(bullets, player);
        spawnenemies(mg, enemies, player, bullets, 3, 2);
        wavelogic(player, bullets);
        coinlogic(player);
        if (player.invincibile && currentstate == state::inwave)
            player.invincibilty += GetFrameTime();

        if (player.invincibilty >= 3 && currentstate == state::inwave)
        {
            player.invincibile = false;
            player.invincibilty = 0;
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            player.health = 0;
            currentstate = state::indeath;
        }

        if (IsKeyPressed(KEY_F9) && player.debug) 
        {
            currentstate = state::inworld;
        }
    }

void wavelogic(Player& player, std::vector<Bullet>& bullets)
{
    if (currentstate == state::inwave)
    {
        if (totalSpawnedEnemies >= maxenemies && enemies.size() == 0 && coins.size() == 0)
        {
            currentstate = state::inworld;
            bullets.clear();
            player.position.x = 640 + player.size.x;
            player.position.y = 360 + player.size.y;
            enemies.clear();
            totalSpawnedEnemies = 0;
        }
    }
}
void coinlogic(Player& player)
{
    for(Coin& c: coins)
    {
        if (Vector2Distance(player.position, c.position) < 100)
        {
            c.position -= Vector2Normalize(Vector2Subtract(c.position, player.position)) * GetFrameTime() * 1000;
        }
        if(CheckCollisionCircleRec(c.position, 20, {player.position.x, player.position.y, player.size.x, player.size.y}))
        {
            c.active = false;
            money += c.value;
            PlaySound(coinpickup);
        }
    }
    coins.erase(std::remove_if(coins.begin(), coins.end(), [](Coin& c) {
        return !c.active;
    }), coins.end());
}
bool soundplayed = false;
bool cardhover = false;
void shoplogic(Player& player)
{
    DrawRectWithOutline(300, 170, 680, 380, 4, (Color){117, 50, 51, 255}, (Color){218, 87, 87, 255});
    SetSoundVolume(selectsound, 0.1);
    float pitch = GetRandomValue(95, 105);
    SetSoundPitch(selectsound, pitch / 100);
    // Draw all cards
    for (size_t i = 0; i < freestock.size(); i++)
    {
        if (freestock[i].name == "healthcard")
            DrawTexture(healthplusspr, freestock[i].position.x, freestock[i].position.y, WHITE);
        else if (freestock[i].name == "riflecard")
            DrawTexture(riflecardspr, freestock[i].position.x, freestock[i].position.y, WHITE);
    }

    bool hoveringAny = false; // Tracks if mouse is over any card

    for (int i = 0; i < freestock.size();i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(), {freestock[i].position.x, freestock[i].position.y, 100, 150}))
        {
            hoveringAny = true;
            if (freestock[i].position.y == 200) freestock[i].position.y = 190;
            else if (freestock[i].position.y == 376) freestock[i].position.y = 366;
            DrawTexture(cardselect, freestock[i].position.x - 5, freestock[i].position.y - 5, WHITE);
            DrawTexture(carddesc, freestock[i].position.x - 65, freestock[i].position.y - 130, WHITE);
            DrawTextEx(pixel, freestock[i].description.c_str(), {freestock[i].position.x - 20, freestock[i].position.y - 85}, 15, 1, BLACK);
            if (!soundplayed) 
            {
                PlaySound(selectsound);
                soundplayed = true;
            }
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {

            }
            break; 
        }
        else
        {
            if (shopstock[i].position.y == 190) shopstock[i].position.y = 200;
            else if (shopstock[i].position.y == 366) shopstock[i].position.y = 376;
        }
    }
    if (!hoveringAny)
    {
        soundplayed = false;
    }
}
void debugmenu(Player& player)
{
            DrawTextEx(pixel,TextFormat("State: %d", (int)currentstate), {10 ,50}, 20,0, GREEN);
            DrawTextEx(pixel,TextFormat("Portal type: %d", (int)currentPortal), {10, 80}, 20,0, GREEN);
            DrawTextEx(pixel, TextFormat("Player alive: %s", player.alive ? "true" : "false"), {10, 110}, 20,0, GREEN);
            DrawTextEx(pixel,TextFormat("Enemies: %d", (int)enemies.size()), {10, 140}, 20,0, ORANGE);
            DrawTextEx(pixel, TextFormat("Castleguards: %d", (int)castleguards.size()), {10, 170}, 20,0, ORANGE);
            DrawTextEx(pixel, TextFormat("Bullets: %d", (int)bullets.size()), {10, 200},20, 0, ORANGE);
            DrawTextEx(pixel, TextFormat("Coins: %d", (int)coins.size()), {10, 230}, 20,0, ORANGE);
            DrawTextEx(pixel, TextFormat("Spawned enemies: %i", totalSpawnedEnemies), {10, 260}, 20,0, ORANGE);
            DrawTextEx(pixel,TextFormat("max enemies: %i", maxenemies), {10, 290}, 20,0, ORANGE);
            DrawTextEx(pixel, TextFormat("Mouse X: %d", GetMouseX()), {10, 320}, 20, 0, GREEN);
            DrawTextEx(pixel, TextFormat("Mouse Y: %d", GetMouseY()), {10, 350}, 20, 0, GREEN);
}