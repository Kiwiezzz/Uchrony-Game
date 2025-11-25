#pragma once

#include "Utils/Assets.hpp"

class Entity : public SpriteAsset
{
    //Virtual le pide al compilador que revise lo que hace la función en tiempo de ejecución
    virtual void init() = 0;
    virtual void handleEvent(sf::Event event) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    virtual ~Entity() = default;
};