#include <raylib.h>
int main()
{
    InitWindow(1280, 720, "fighting niggas");
    SetTargetFPS(60);


    Rectangle player1 = {300, 640, 40, 40};
    Rectangle player1hb = {player1.x + player1.width, player1.y, 10, 40};
    Rectangle player1hpbar = {100, 50, 200,20};
    Rectangle mana1bar = {120, 60, 100,20};
    Rectangle proj1 = {player1.x + player1.width / 2, player1.y + player1.height / 2, 10, 10};
     
    int player1hp = 20;
    int mana1 = 0;

    bool proj1active = false;
    bool player1onground = true;

    Rectangle player2 = {1000, 640,40 ,40};
    Rectangle player2hb = {player2.x + player2.width, player2.y, 10, 40};
    Rectangle player2hpbar = {780, 50, 200,20};

    int player2hp = 20;
    int mana2 = 0;

    bool proj2active = false;
    bool player2onground = true;

    Rectangle ground = {0, 680, 1280,40};



    Vector2 player1velo = {0, 0};
    Vector2 player2velo = {0, 0};


    float gravity = 0.5;

    Texture2D sigma = LoadTexture("/home/atyeb/Downloads/player1.png");
    Rectangle sigmasource = { 0, 0, (float)sigma.width, (float)sigma.height };

    Vector2 sigmapos = {player1.x, player1.y};

    while (!WindowShouldClose())
    {

        player1hpbar.width = player1hp * 20;

        mana1bar.width = mana1 * 20;

        player1.y += player1velo.y;
        player1hb.y = player1.y;


        if(IsKeyDown(KEY_D))
        {
            player1.x += 5;
            player1hb.x = player1.x + player1.width;

        }  
        if(IsKeyDown(KEY_A))
        {
            player1.x -= 5;
            player1hb.x = player1.x - player1hb.width;

        }  
        if(IsKeyDown(KEY_W) && player1onground == true)
        {
            player1velo.y = -10;
            player1onground = false;
           player1hb.y = player1.y;
        }  



        if(CheckCollisionRecs(player1, ground))
        {
            player1.y = ground.y - player1.height;
            player1hb.y = ground.y -player1.height;
            player1onground = true;
            player1velo.y = 0;
        }
            if (!player1onground)
        {
            player1velo.y += gravity;
        }

        if(IsKeyPressed(KEY_SPACE) && CheckCollisionRecs(player1hb, player2))
        {
            player2hp--;
            if(mana1 < 15) mana1 += 3;
        }

        if(IsKeyPressed(KEY_E) && mana1 == 15)
        {
            proj1.x = player1.x + player1.width / 2;
            proj1.y = player1.y + player1.height / 2;
            proj1active = true;
            mana1 -= 15;
        }
        if(proj1active)
        {
            proj1.x += 3;
        }
        if(CheckCollisionRecs(player2, proj1))
        {
            player2hp -= 10;
            proj1active = false;
        }
        
        // player2 shenanigans
        player2.y += player2velo.y;
        player2hb.y = player2.y;
        player2hpbar.width = player2hp * 20;

        if(IsKeyDown(KEY_RIGHT))
        {
            player2.x += 5;
            player2hb.x = player2.x + player2.width;

        }  
        if(IsKeyDown(KEY_LEFT))
        {
            player2.x -= 5;
            player2hb.x = player2.x - player2hb.width;

        }  
        if(IsKeyDown(KEY_UP) && player2onground == true)
        {
            player2velo.y = -10;
            player2onground = false;
           player2hb.y = player2.y;
        }  



        if(CheckCollisionRecs(player2, ground))
        {
            player2.y = ground.y - player2.height;
            player2hb.y = ground.y -player2.height;
            player2onground = true;
            player2velo.y = 0;
        }
            if (!player2onground)
        {
            player2velo.y += gravity;
        }

        
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionRecs(player2hb, player1))
        {
            player1hp -= 1;

        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleRec(player1, RAYWHITE);
        DrawRectangleRec(player1hb, RED);
        DrawRectangleRec(player1hpbar, GREEN);
        DrawRectangleRec(mana1bar, BLUE);
        DrawRectangleRec(player2, PURPLE);
        DrawRectangleRec(player2hb, RED);
        DrawRectangleRec(player2hpbar, GREEN);
        DrawTexturePro(sigma, sigmasource, player1, {0,0}, 0, WHITE);

        DrawRectangleRec(ground, GRAY);
        
        if(proj1active)
        {
            DrawRectangleRec(proj1, RED);
        }

        EndDrawing();    
    }
    CloseWindow();
}
