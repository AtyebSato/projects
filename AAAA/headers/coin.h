#ifndef COIN_H
#define COIN_H

#include "assets.h"
#include <raylib.h>

class Coin{
    public:
    Vector2 position;
    bool active;
    int value;
    Texture2D* sprite;
    Coin(int value, Texture2D* sprite, Vector2 position = {0,0}, bool active = true){
        this->position = position;
        this->active = active;
        this->value = value;
        this->sprite = sprite;
    }
};
extern Coin goldcoin;
extern Coin diamondcoin;
#endif