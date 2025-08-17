#include "headers/bullet.h"
#include <raylib.h>
#include <vector>

Bullet::Bullet(Vector2 position, Vector2 dir, bool active, float damage, int radius) {
    this->position = position;
    this->dir = dir;
    this->active = active;
    this->damage = damage;
    this->radius = radius;
}
std::vector<Bullet> bullets;