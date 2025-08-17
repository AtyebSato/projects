#ifndef ENEMY_H
#define ENEMY_H
#include "assets.h"
#include <raylib.h>
#include <vector>
    class Enemy{
        public:
        int damage;
        int health;
        int speed;
        Texture2D* texture;
        Texture2D* texturehit;
        Vector2 size;
        Vector2 position;
        Vector2 dir;
        bool alive;
        bool hit;
        float hittime;
        Enemy(int damage, int health, int speed, Texture2D* texture, Texture2D* texturehit,Vector2 size,Vector2 position = {0,0}, Vector2 dir = {0,0}, bool alive = true, bool hit = false, float hittime = 0){
            this->position = position;
            this->dir = dir;
            this->alive = alive;
            this->hit = hit;
            this->hittime = hittime;
            this->damage = damage;
            this->health = health;
            this->speed = speed;
            this->texture = texture;
            this->texturehit = texturehit;
            this->size = size;
        }
    };
    extern Enemy cg;
    extern Enemy mg;
#endif