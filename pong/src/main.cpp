#include <cmath>
#include <iostream>
#include <raylib.h>

int main ()
{
    InitWindow(1280, 720, "pong");
    SetTargetFPS(60);

    Font Roboto = LoadFont("/usr/share/fonts/TTF/RobotoMono-Medium.ttf");
    Rectangle player1 = { 20, (360 - player1.height / 2), 15, 130};
    Rectangle player2 = {1250, (360 - player2.height / 2 ), 15, 130};


    Vector2 ball {640, 360};
    Vector2 velo {10,0};

    float veloinc = 0.9;

    int score1 = 0;
    int score2 = 0;

    Vector2 textscore1 = {50, 50};
    Vector2 textscore2 = {1180, 620};
    while (!WindowShouldClose())
    {


        ball.x += velo.x;
        ball.y += velo.y;

        
        if (ball.y + 10 <= 20|| ball.y + 10 >= 720)
        {
            velo.y = -velo.y;
        }

        if (CheckCollisionCircleRec(ball, 10, player1))
        {
            float player1center = player1.y + player1.height / 2;
            float relativeY = (ball.y - player1center) / (player1.height / 2 ); 
            velo.x = std::fabs(velo.x); 
            velo.y = relativeY * 6;
            veloinc *= 1.2;
            velo.x += veloinc;
            std::cout << veloinc;
        }

         
        if (CheckCollisionCircleRec(ball, 10, player2))
        {
            float player2center = player2.y + player2.height / 2;
            float relativeY = (ball.y - player2center) / (player2.height / 2 );
            velo.x = -std::fabs(velo.x); 
            velo.y = relativeY * 3;
            velo.x *= 0.9;
        }

        // if(IsKeyDown(KEY_UP) && player2.y  > 0 )
        // {
        //    player2.y -=6;
        // }
        // if(IsKeyDown(KEY_DOWN) && player2.y + player2.height < 720)
        // {
        //  player2.y +=6;
        //}

        if(IsKeyDown(KEY_W) && player1.y > 0)
        {
            player1.y -=6;
        }
        if(IsKeyDown(KEY_S) && player1.y + player1.height < 720)
        {
            player1.y +=6;
        }
        
        if(ball.x >= 1300)
        {
        {
            score1++;
            ball.x = 640;
            ball.y = 360;
            player1.y = (360 - player1.height / 2);
            player2.y = (360 - player2.height / 2);
            velo.x = 0;
            velo.y = 0;
            WaitTime(1);
            velo.x = 10;
        }
        }
        if(ball.x <= -20)
        {
            score2++;
            ball.x = 640;
            ball.y = 360;
            player1.y = (360 - player1.height / 2);
            player2.y = (360 - player2.height / 2);
            velo.x = 0;
            velo.y = 0;
            WaitTime(1);
            velo.x = 10;
        }
        player2.y = ball.y - player2.height;



        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleRec(player1, WHITE);
        DrawRectangleRec(player2, WHITE);


        DrawCircleV(ball, 10, WHITE);

        DrawTextEx(Roboto, TextFormat("%i", score1),textscore1, 60, 10, WHITE);
        DrawTextEx(Roboto, TextFormat("%i", score2),textscore2, 60, 10, WHITE);
        EndDrawing();
    }
    CloseWindow();
}