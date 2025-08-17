#ifndef PORTAL_H
#define PORTAL_H
#include <raylib.h>
#include <vector>
#include "bullet.h"
#include "enums.h"
#include "player.h"
    struct Portal{
        Vector2 position;
        bool selected;
        bool valid;
        Portaltype portaltype;
    };
void spawnportals(std::vector <Portal>& portals);
void castleportlogic(std::vector<Bullet>& bullets, Player& player);
void worldlogic(Player& player);
void deathlogic(Player& player);
void redportlogic(std::vector<Bullet>& bullets, Player& player);
void wavelogic(Player& player, std::vector<Bullet>& bullets);
void shoplogic(Player& player);
void debugmenu(Player& player);
extern std::vector<Portal> portals;
extern int spawned_enemies;
#endif