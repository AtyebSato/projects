#include "headers/assets.h"
#include <raylib.h>
class Enemy{
    public:

    int damage;
    int health;
    int speed;
    Texture2D * texture;
    Texture2D *texturehit;
    Vector2 size;
    Vector2 position = {0,0};
    Vector2 dir = {0,0};
    bool alive = false;
    bool hit = false;
    float hittime = 0;
    Enemy(int damage, int health, int speed, Texture2D* texture, Texture2D* texturehit,Vector2 size, Vector2 position = {0,0}, Vector2 dir = {0,0}, bool alive = true, bool hit = false, float hittime = 0){
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

    Enemy cg(1,2,200, &castleguard, &castleguardhit, (Vector2){40,40});
    Enemy mg(2,4,150, &magma, &magmahit, (Vector2){60,60});

