#include <cmath>

#include <vector>

#include <raylib.h>
#include <raymath.h>

#include "headers/bullet.h"
#include "headers/Enemies.h"
#include "headers/assets.h"
#include "headers/functions.h"
#include "headers/logic.h"
#include "headers/enums.h"
#include "headers/player.h"
#include "headers/globals.h"
#include "headers/cards.h"
#define RAYGUI_IMPLEMENTATION
#include "headers/raygui.h"

int main()
{
    InitWindow(1280, 720, "i dont even know");
    InitAudioDevice();
    LoadGameTextures();
    HideCursor();
    GuiLoadStyle("/home/atyeb/Projects/AAAA/style_cherry.rgs");
    Font roboto = LoadFont("/usr/share/fonts/TTF/RobotoMono-Medium.ttf");
    Font pixel = LoadFont("images/PixelPurl.ttf");
    GuiSetFont(pixel);

    Texture2D magmafloor = LoadTexture("/home/atyeb/Projects/AAAA/images/magmafloor.png");
    Color background = { 11, 22, 46, 255};
    
    std::vector<Bullet> bullets;
    spawnportals(portals);

    Player player = {640,360,3,false, 0, {40,40}, 1, false};


    int tiles[32][18];
    for (int i = 0; i < 32;i++)
    {
        for (int n = 0; n < 18;n++)
        {
            tiles[i][n] = (int)GetRandomValue(1, 4);
        }
    }

    int cardtype;
    int cardx = 356;
    int cardy = 200;
    bool rifleinshop = false;
    for(int i = 0; i < 4; i++)
    {
        cardtype = GetRandomValue(1, 3);
        for (Card c : freestock)
        {
            if (c.name == "rifelcard")
            {
                rifleinshop = true;
            }
        }
        if (!rifleinshop)
        {
            if (cardtype == 1) freestock.push_back(Card(&refillriflecard,"riflerefill", 60, "Refills rifle ammo", {(float)cardx, (float)cardy}));
            else if(cardtype == 2) freestock.push_back(Card(&healthplusspr,"healthcard",50, "Adds one heart to health", {(float)cardx, (float)cardy}));
            else if(cardtype == 3) freestock.push_back(Card(&riflecardspr, "riflecard", 100,"Unlocks a faster less\npowerfull weapon\nwith limited ammo", {(float)cardx, (float)cardy}));
        }
    }
    for(int i = 0; i < 4; i++)
    {
        cardtype = GetRandomValue(1, 2);
        for(Card c : shopstock)
        {
            if (c.name == "riflecard") rifleinshop = true;
        }
        if(cardtype == 1) shopstock.push_back(Card(&healthplusspr, "healthcard",healthprice, "Adds one heart to health",{(float)(cardx),(float)cardy}));
        else if (cardtype == 2 && !rifleinshop) 
        {
            shopstock.push_back(Card(&riflecardspr, "riflecard", rifleprice,"Unlocks a faster less\npowerfull weapon\nwith limited ammo",{(float)cardx, (float)cardy}));
        }
        else shopstock.push_back(Card(&healthplusspr, "healthcard", healthprice, "Adds one heart to health",{(float)(cardx),(float)cardy}));
        cardx += 156;
    }
    Rectangle playerrec = {player.position.x,player.position.y,40,40};
    
    float deltatime = GetFrameTime();

    Vector2 mouse = GetMousePosition();

    short fps = GetFPS();

    bool tpprompt = false;
    
    int x = 0;

    while(!WindowShouldClose())
    {
        
    if(player.alive && currentstate == state::inwave && currentPortal == Portaltype::castleport ) castleportlogic(bullets, player); killing(enemies, bullets, 20 , 10,70);

    if(player.alive && currentstate == state::inwave && currentPortal == Portaltype::red ) redportlogic(bullets, player); killing(enemies, bullets, 100 , 0, 0);

    if(player.alive && currentstate == state::inworld  ) worldlogic( player);

    if(currentstate == state::indeath) deathlogic(player);

    if (player.health <= 0) currentstate = state::indeath;        

    if (IsKeyPressed(KEY_F1)) inshop = true;

    if (IsKeyPressed(KEY_F10) && player.debug) player.health++;

        BeginDrawing();
        ClearBackground(background);
        if(player.alive && currentstate == state::inwave )
        {
            if (currentPortal == Portaltype::castleport)
            {
                for(int y = 0; y < 19; y++)
                {
                    for(int x = 0; x < 33;x++)
                    {
                        DrawTexture(castletile2, x * 40, y * 40, WHITE);
                    }
                }
                drawenemies(enemies, player);
            }
            else if (currentPortal == Portaltype::red)
            {
                for(int y = 0; y < 19; y++)
                {
                    for(int x = 0; x < 33;x++)
                    {
                        DrawTexture(magmafloor, x * 40, y * 40, WHITE);
                    }
                }
                drawenemies(enemies, player);
            }
            for(Bullet& b: bullets)
            {
                DrawTextureEx(bulletsprite, b.position, 0, (float)b.radius / 10, ORANGE);
            }
        }
        else if(currentstate == state::indeath)
        {
            DrawTextEx(roboto, "GAME OVER", {500,300}, 40, 0, RED);
            DrawTextEx(roboto, "Press space to restart", {500,350}, 20, 1, WHITE);
        }
        if(currentstate == state::inmenu)
        {
            if(GuiButton({540,310,200,100}, "Start the game")) 
            {
                loading = true;
                currentstate = state::inworld;
            }
            GuiCheckBox({590, 450,20,20}, "Debug", &player.debug);
            DrawTextureEx(menucurs, GetMousePosition(), 0, 1, WHITE);
        }
        if (currentstate == state::inwave && player.alive )
        {
            if (!player.invincibile) DrawTexture(playersprite, player.position.x, player.position.y, WHITE);
            else if (player.invincibile) DrawTextureEx(invincibilesprite, {player.position.x, player.position.y}, 0, 1, WHITE);
            if(currentweapon == weapons::pistol)
            {
                if(GetMouseX() > player.position.x + 20 && currentstate == state::inwave)
                {
                Vector2 gunPos = {player.position.x + player.size.x / 2, player.position.y + player.size.y / 2};
                Vector2 mouse = GetMousePosition();
                Vector2 direction = Vector2Subtract(mouse, gunPos);
                float angle = atan2f(direction.y, direction.x) * RAD2DEG;

                DrawTextureEx(gun, gunPos, angle, 0.7, WHITE);
                }
                else if (currentstate == state::inwave && player.alive) {
                    Vector2 gunPos = {player.position.x + player.size.x / 2, player.position.y + player.size.y / 2 + 20};
                    Vector2 mouse = GetMousePosition();
                    Vector2 direction = Vector2Subtract(mouse, gunPos);
                    float angle = atan2f(direction.y, direction.x) * RAD2DEG;
                    Rectangle src = { 0, 0, (float)gun2.width, (float)gun2.height };
                    Rectangle dest = { player.position.x + player.size.x / 2, player.position.y + player.size.y / 2, gun2.width * 0.7f, gun2.height * 0.7f };
                    Vector2 origin = {0,23};
                    DrawTexturePro(gun2, src, dest, origin, angle, WHITE);

                }
            }
            else if (currentweapon == weapons::rifle)
            {
                if(GetMouseX() > player.position.x + 20 && currentstate == state::inwave)
                {
                    Vector2 gunPos = {player.position.x + player.size.x / 2, player.position.y + player.size.y / 2 + 20};
                    Vector2 mouse = GetMousePosition();
                    Vector2 direction = Vector2Subtract(mouse, gunPos);
                    float angle = atan2f(direction.y, direction.x) * RAD2DEG;
                    Rectangle src = { 0, 0, (float)riflesprite2.width, (float)riflesprite2.height };
                    Rectangle dest = { player.position.x + player.size.x / 2, player.position.y + player.size.y / 2 + 10, riflesprite2.width * 0.7f, riflesprite2.height * 0.7f };
                    Vector2 origin = {24,15};
                    DrawTexturePro(riflesprite, src, dest, origin, angle, WHITE);
                }
                else if (currentstate == state::inwave && player.alive) {
                    Vector2 gunPos = {player.position.x + player.size.x / 2, player.position.y + player.size.y / 2 + 20};
                    Vector2 mouse = GetMousePosition();
                    Vector2 direction = Vector2Subtract(mouse, gunPos);
                    float angle = atan2f(direction.y, direction.x) * RAD2DEG;
                    Rectangle src = { 0, 0, (float)riflesprite2.width, (float)riflesprite2.height };
                    Rectangle dest = { player.position.x + player.size.x / 2, player.position.y + player.size.y / 2, riflesprite2.width * 0.7f, riflesprite2.height * 0.7f };
                    Vector2 origin = {24,24};
                    DrawTexturePro(riflesprite2, src, dest, origin, angle, WHITE);
                }
                DrawTextOutlined(pixel, TextFormat("%i", rifleammo), {1230,45}, 40, 0, BLACK, WHITE, 4);
            }
            for (int i = 1 ; i < player.health + 1; i++)
            {
                int x = i * 50;
                DrawTextureEx(heart, {static_cast<float>(x), 50}, 0, 1, WHITE);
                
            }

        }


        if(player.debug && currentstate == state::inmenu) GuiTextBox({540, 490, 200, 100}, (char*)"-Press F10 to increase health\n-Press F9 to clear current portal", 40, false);
        if (currentstate == state::inworld )
        {
            for(int y = 0; y < 18; y++)
            {
                for(int x = 0; x < 32;x++)
                {
                    switch (tiles[x][y]) {
                        case 1: DrawTexture(grass, x *40, y * 40, GREEN); break;
                        case 2: DrawTexture(grass2, x * 40, y * 40, GREEN); break;
                        case 3: DrawTexture(grass3, x * 40, y * 40, GREEN); break;
                        case 4: DrawTexture(grass4, x * 40 , y * 40, GREEN); break;
                    }

                }
            }
            for(Portal& p : portals)
            {
                if(p.portaltype == Portaltype::red) DrawTexture(portalred, p.position.x, p.position.y, WHITE);
                else if(p.portaltype == Portaltype::castleport) DrawTexture(portal, p.position.x, p.position.y, WHITE);
                if (p.selected == true) 
                {
                    DrawTexture(portalselected, p.position.x, p.position.y, WHITE);
                    DrawTextEx(pixel, "Press F to enter", {player.position.x - 50, player.position.y + 50}, 20, 1, RED);
                    if(player.debug) 
                    {
                        if (p.portaltype == Portaltype::red) DrawText("Portal type: red", player.position.x - 75, player.position.y - 75, 20, RED);
                        if (p.portaltype == Portaltype::castleport) DrawText("Portal type: castle", player.position.x - 75, player.position.y - 75, 20, RED);
                    }   
                }
            }
            DrawTextureEx(playersprite,{player.position.x, player.position.y},0, 1,WHITE);
            if(GuiButton({20,(float)720 / 2 - (float)75 / 2,150,75}, "SHOP")) inshop = !inshop;
        }

        if (player.debug) for(Portal& p : portals){DrawLine(player.position.x + 20, player.position.y + 20, p.position.x + 30, p.position.y + 50, RED);}
        for (Enemy& e: castleguards)
        {
            if (!e.hit)DrawText("false", 100, 100, 20, WHITE);
            if (player.debug) DrawRectangle(e.position.x, e.position.y, e.size.x, e.size.y, RED);
        }
        if (player.debug) debugmenu(player);

        if (currentstate == state::inwave || currentstate == state::inworld ) DrawTextOutlined(pixel, TextFormat("%i$", money), {50,90}, 40, 1, BLACK, GREEN, 3);

        if (loading)
        {
            DrawRectangle(x, 0, 1280, 720, BLACK);
            x += 7500 * GetFrameTime();
            if (x > 1280)
            {
                loading = false;
                x = 0;
            }
        }
        if (inshop) 
        {
            shoplogic(player);
            for (int i = 1 ; i < player.health + 1; i++)
            {
                int x = i * 50;
                DrawTextureEx(heart, {static_cast<float>(x), 50}, 0, 1, WHITE);
                
            }
        }
        if (currentstate == state::inwave || currentstate == state::inworld )
        {
            DrawTextureEx(cursor, GetMousePosition(), 0, 2, RED);
        }
        EndDrawing();   
    }

    CloseWindow();
}