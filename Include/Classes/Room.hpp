#pragma once

#include <unordered_map>

#include <Assets.hpp>
#include <NPC.hpp>
#include "Classes/Entity.hpp"

using namespace std;

class Room
{
    /// @brief SpriteAsset del fondo
    SpriteAsset background;

    /// @brief ImageAsset de la imagen de colision
    ImageAsset collision;

    /// @brief Se usa para path finder. Depende del collision
    NavGrid navGrid;

    unordered_map<string, Entity> entities;
    
public:

    void init();

    void handleEvent(sf::Event event);

    void update(sf::Time dt);

    void render(sf::RenderWindow& window);
};