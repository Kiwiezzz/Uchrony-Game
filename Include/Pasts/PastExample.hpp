#pragma once
// [DEPRECATED] Esta clase es un remanente del sistema antiguo.
// Usar GenericScene y SceneRegistry para nuevas escenas.

#include "Classes/Past.hpp"
#include "Entities/NPC.hpp"
#include "Classes/GameManager.hpp"
#include "Entities/Item.hpp"
#include <memory>
#include <optional>
#include <map>

class PastExample : public Past //:GameState
{
public:
    /// @brief carga los diferentes rooms
    void init() override;

    
    /// @brief Se encarga de manejar los eventos (inputs) que suceden, por lo general mas a nivel global
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    
    /// @brief 
    /// @param dt 
    void update(sf::Time dt) override;

    void render(sf::RenderWindow& window) override;

private:
    // Variables para drag & drop de items en inventario
    std::optional<Item> draggingItem;
    int draggingFrom = -1;

    std::map<std::string, sf::FloatRect> doorTriggers;
    
    bool m_pendingRoomSwitch = false;
    Room* m_pendingNextRoom = nullptr;
    Pathfinder pathfinder;
};