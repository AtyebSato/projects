#include <raylib.h>
#include <vector>
#include <raymath.h>
#include <algorithm>

int main()
{
  InitWindow(1280, 720, "Rogue Like");
  SetTargetFPS(60);

  Font roboto = LoadFont("/usr/share/fonts/TTF/RobotoMono-Medium.ttf");

  struct Bullet{
    Vector2 pos;
    Vector2 dir {0,0};
    bool active = true;
    float speed = 6;
  };

  std::vector<Bullet> bullets;

  struct Enemy{

    Vector2 pos;
    Vector2 dir {0, 0};
    bool alive = true;
    float speed = 3;
  };
  std::vector<Enemy> enemies;
  Vector2 mouse;


  float spawntimer = 0;
  bool invincible;
  float invinciblity = 0;
  float deltatime;

  Vector2 enemyspawn;
  Rectangle player {640, 360,40,40};

  int health = 3;
  int healthx = 100;
  while (!WindowShouldClose())
  {
    deltatime = GetFrameTime();
    spawntimer += deltatime;

    mouse.x = GetMouseX();
    mouse.y = GetMouseY();
    
    

    if (spawntimer >= 1)
    {
      enemyspawn = { (float)GetRandomValue(0 , 1280), (float)GetRandomValue(0, 720) };
      enemies.push_back({ enemyspawn}); 
      spawntimer = 0; 
    }
    for (Enemy& e : enemies)
    {
      if (e.alive)
      {
        e.pos.x += e.dir.x * e.speed;
        e.pos.y += e.dir.y * e.speed;
        e.dir = Vector2Normalize(Vector2Subtract({player.x + player.width / 2, player.y + player.height / 2}, e.pos));
      }

    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {

      Vector2 mouse = { (float)GetMouseX(), (float)GetMouseY() };
      Vector2 playerCenter = { player.x + player.width / 2, player.y + player.height / 2 };
      Vector2 dir = Vector2Normalize(Vector2Subtract(mouse, playerCenter));
      bullets.push_back({ playerCenter, dir  });
    }

    for(Bullet& b : bullets)
    {
      b.pos.x += b.dir.x * b.speed;
      b.pos.y += b.dir.y * b.speed;
    }
    
    if(IsKeyDown(KEY_D)) player.x += 3;
    if(IsKeyDown(KEY_A)) player.x -= 3;
    if(IsKeyDown(KEY_S)) player.y += 3;
    if(IsKeyDown(KEY_W)) player.y -= 3;
    
    for(Bullet& b: bullets)
    {
      for (Enemy& e : enemies)
      {
        Rectangle enemyrec = {e.pos.x, e.pos.y, 40 ,40};

        if (CheckCollisionCircleRec(b.pos, 5, enemyrec) && b.active && e.alive)
        {
          b.active = false;
          e.alive = false;
        }
      }
    }

    for (Enemy e : enemies)
    {
      Rectangle enemyrec = {e.pos.x, e.pos.y, 40 ,40};
      if(CheckCollisionRecs(player, enemyrec) && !invincible) 
      {
        health--;
        invincible = true;
      } 
    }

    if (invincible) invinciblity += deltatime;
    if (invinciblity >= 3)
    {
      invincible = false;
      invinciblity = 0;
    } 
    // Remove inactive bullets
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {
            return !b.active || b.pos.x < 0 || b.pos.x > 1280 || b.pos.y < 0 || b.pos.y > 720;
        }),
        bullets.end()
    );

    // Remove dead enemies
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) {
            return !e.alive;
        }),
        enemies.end()
    );
    BeginDrawing();
    ClearBackground(BLACK);
    for(Bullet b : bullets){
      if (b.active) DrawCircleV(b.pos, 5, RED);
    }
    for(Enemy e : enemies)
    {
     if (e.alive) DrawRectangleV(e.pos, {40, 40}, RED);
    }
    for(int i = 1; i < health + 1 ; i++)
    {
      DrawCircle(healthx * i, 100, 10, RED);

    }
    DrawRectangleRec(player, WHITE);
      if(invincible) DrawRectangle(player.x, player.y, player.width, player.height, GRAY);

    EndDrawing();
  }
  CloseWindow();
}