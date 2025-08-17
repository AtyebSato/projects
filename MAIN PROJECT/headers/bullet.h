#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>
#include <vector>

class Bullet {
public:
    Vector2 position;
    Vector2 dir;
    bool active;
    float damage;
    int radius;
    Bullet(Vector2 position, Vector2 dir, bool active, float damage, int radius);
};

extern std::vector<Bullet> bullets;

#endif
