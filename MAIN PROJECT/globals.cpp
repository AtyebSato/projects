#include "headers/Enemies.h"
#include "headers/cards.h"
#include "headers/coin.h"
#include "headers/logic.h"
#include <vector>
std::vector<Enemy> castleguards;
std::vector<Enemy> magmas;
std::vector<Portal> portals;
std::vector<Enemy> enemies;
std::vector<Coin> coins;
std::vector<Card> shopstock;
std::vector<Card> freestock;
int maxenemies = 3;
int totalSpawnedEnemies = 0;
int money = 0;
bool loading = false;
bool inshop = false;
bool riflebought = false;;
int healthprice = 50;
int rifleprice = 100;
int rifleammo = 100;
int timeshealthbought = 0;
