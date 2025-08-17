#include <raylib.h>
int main()
{
    InitWindow(1280, 720, "Snake");
    SetTargetFPS(60);

    Font roboto = LoadFont("/usr/share/fonts/TTF/RobotoMono-Bold.ttf");

    Vector2 cookie = {640, 360};
    float radius = 30;

    
    int mouseinc = 1;
    int score = 0;

    Rectangle mouseIncUpg = {1000, 50, 200, 30};
    Rectangle autoclick = {1000, 100, 200, 30};

    int autoclickprc = 100;

    int upgrade1round = 20;
    int upgrade1price = 20;

    int autoclickers = 0;

    Vector2 upgra1text = {mouseIncUpg.x + 20, mouseIncUpg.y + 5};
    Vector2 autoclicktxt = {autoclick.x + 20, autoclick.y + 5};
    Vector2 scoretxt = {100, 30};
    Vector2 moneypersec = {100, 50};
    Vector2 autoclickout10;


    float time = 0;

    while(!WindowShouldClose())
    {
        time += GetFrameTime();
        if (time >= 1){
            time = 0;
            score += autoclickers;
        }
        int upgrade1round = 20;
        float mouseY = GetMouseY();
        float mouseX = GetMouseX();

        Vector2 point = {mouseX, mouseY};
        radius = 30;
        cookie.x = 640;
        
        if(CheckCollisionPointRec(point, mouseIncUpg))
        {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if(score > upgrade1price)
                {
                    score -= 20;
                    upgrade1price += 10;
                    upgrade1round = 5;
                    mouseinc++;
                }
            }
        }
        if (CheckCollisionPointCircle(point, cookie, radius))
        {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                score += mouseinc;
                radius = 20;
            }
        }
        if(CheckCollisionPointRec(point, autoclick))
        {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (score >= 100)
                {
                    score -= autoclickprc;
                    autoclickprc += 20;
                    autoclickers++;
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircleV(cookie, radius, WHITE);

        DrawRectangleRounded(mouseIncUpg, upgrade1round, 2, WHITE);
        DrawRectangleRounded(autoclick, 20, 0, WHITE);

        DrawTextEx(roboto,TextFormat("Mouse click +1 %i$" ,upgrade1price) , upgra1text, 20, 0 ,BLACK);
        DrawTextEx(roboto, TextFormat("Money: %i", score), scoretxt, 30, 0, WHITE);
        DrawTextEx(roboto, TextFormat("Money/s %i/s", autoclickers), moneypersec, 30, 0, WHITE);
        DrawTextEx(roboto, TextFormat("Autoclick +1 %i$", autoclickprc), autoclicktxt, 20, 0, BLACK);
        EndDrawing();
        
    }
    CloseWindow();
}