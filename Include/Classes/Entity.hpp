#pragma once

#include <functional>

#include "Utils/Assets.hpp"

/// @brief Es una entidad cualquiera generica:
/// tanto los objetos como el jugador y los npc son entidades
class Entity : public SpriteAsset
{
public:
    Entity() : SpriteAsset()
    {

    }

    Entity(const std::string& path) : SpriteAsset(path)
    {
        
    }

    Entity(const Entity& entityCopy) : SpriteAsset(*this)
    {

    }

    virtual ~Entity() = default;

    void setInteraction(std::function<void()> interaction)
    {
        m_interaction = interaction;
    }

    void interact()
    {
        m_interaction();
    }
    
private:
    //Virtual le pide al compilador que revise lo que hace la función en tiempo de ejecución
    virtual void init() = 0;
    virtual void handleEvent(sf::Event event) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void aproach();


    std::function<void()> m_interaction;
};