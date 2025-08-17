#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include "Enemies.h"
#include "cards.h"
#include "coin.h"
#include "logic.h"
#include "bullet.h"

extern std::vector<Bullet> bullets;
extern std::vector<Enemy> castleguards;
extern std::vector<Enemy> magmas;
extern std::vector<Portal> portals;
extern std::vector<Enemy> enemies;
extern std::vector<Coin> coins;
extern std::vector<Card> shopstock;
extern std::vector<Card> freestock;
extern float timer;
extern int totalSpawnedEnemies;
extern int maxenemies;
extern int money;
extern bool loading;
extern state currentstate;
extern Portaltype currentPortal;
extern bool inshop;
extern int healthprice;
extern int timeshealthbought;
extern int rifleprice;
extern int rifleammo;
extern bool riflebought;
#endif
