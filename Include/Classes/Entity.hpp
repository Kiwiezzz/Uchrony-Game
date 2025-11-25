#pragma once

#include "Utils/Assets.hpp"

/// @brief Es una entidad cualquiera generica:
/// tanto los objetos como el jugador y los npc son entidades
class Entity : public SpriteAsset
{
public:
    Entity(const std::string& path) : SpriteAsset(path)
    {
        
    }

    Entity(const Entity& entityCopy) : SpriteAsset(*this)
    {

    }

    virtual ~Entity() = default;
    
private:
    //Virtual le pide al compilador que revise lo que hace la función en tiempo de ejecución
    virtual void init() = 0;
    virtual void handleEvent(sf::Event event) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

};