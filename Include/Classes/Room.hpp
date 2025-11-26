#pragma once

#include <unordered_map>

#include "Utils/Assets.hpp"
#include "Entities/NPC.hpp"
#include "Classes/Entity.hpp"
#include "Utils/Pathfinder.hpp"
#include "Utils/GameUtilities.hpp"

// Forward declaration
class Game;

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

    unordered_map<string, Entity*> entities;
    unordered_map<string, NPC> npcs;
    
    /// @brief Pathfinder para calcular rutas en el room
    Pathfinder pathfinder;
    
    /// @brief Puntero a Game para cambiar de estado (ej: abrir diálogos)
    Game* game;


public:

    void init();

    void handleEvent(sf::Event& event, sf::RenderWindow& window);

    void update(sf::Time dt);

    void render(sf::RenderWindow& window);

    void setBackground(std::string path);

    SpriteAsset& getBackground();

    void setCollisionAndGrid(std::string path);

    /// @brief Agrega a la tabla hash de entities una entity
    /// @param name
    /// @param entity 
    void addEntity(const std::string& name, Entity* entity);

    /// @brief Busca en la tabla hash de entities y retorna una referencia a ella
    /// @param name 
    /// @return 
    Entity& getEntity(std::string name);

    /// @brief Agrega a la tabla hash de npcs un npc
    void addNpc(const std::string& name, NPC& entity);

    /// @brief Busca en la tabla hash de npcs y retorna una referencia a él
    NPC& getNpc(std::string name);

    /// @brief Obtiene el NavGrid del room para pathfinding
    const NavGrid& getNavGrid() const;

    /// @brief Establece el puntero a Game para cambios de estado
    void setGame(Game* g);

    Entity& operator=(const Entity& other);
};