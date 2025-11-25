#pragma once

#include <unordered_map>

#include "Utils/Assets.hpp"
#include "Entities/NPC.hpp"
#include "Classes/Entity.hpp"

using namespace std;

/// @brief t
class Room
{
protected:
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

    void setBackground(std::string path);

    void setCollisionAndGrid(std::string path);

    void addEntity(const std::string& name, Entity& entity);

    const Entity& getEntity(std::string name);
};