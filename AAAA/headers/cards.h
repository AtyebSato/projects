#ifndef CARDS_H
#define CARDS_H

#include <raylib.h>
#include <iostream>
#include <string>
class Card{
    public:
    Texture2D* sprite;
    std::string name;
    int price;
    std::string description;
    Vector2 position;
    Card(Texture2D* sprite, std::string name, int price, std::string description, Vector2 position = {0,0}){
        this->position = position;
        this->sprite = sprite;
        this->name = name;
        this->price = price;
        this->description = description;
    }
};
#endif