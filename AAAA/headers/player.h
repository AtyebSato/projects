#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
struct Player{
    Vector2 position;
    int health;
    bool invincibile;
    float invincibilty;
    Vector2 size;
    bool alive;
    bool debug;
};
#endif