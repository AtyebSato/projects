#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include <cstddef>
#include <raylib.h>
#include <vector>
#include "bullet.h"
#include "Enemies.h"
#include "player.h"
extern float timer;

void charactermovment(Player& player, int speed = 300);
void shoot(std::vector<Bullet>& bullets, Player& player);
void spawnenemies(Enemy& enemy, std::vector<Enemy>& enemiesvec, Player& player, std::vector<Bullet>& bulletvec, int maxenemies, float spawntime);
void drawenemies(std::vector<Enemy>& enemyvec, Player& player);
void killing(std::vector<Enemy>& enemyvec, std::vector<Bullet>& bullets, int goldchance, int diamondchance, int silverchance);
void coinlogic(Player& player);
void DrawTextOutlined(Font font, const char* text, Vector2 pos, float fontSize, float spacing, Color outlineColor, Color textColor, int thickness);
void DrawRectWithOutline(int x, int y, int width, int height, int thickness, Color color, Color outlineColor);
#endif
