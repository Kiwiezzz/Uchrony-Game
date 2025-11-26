#pragma once

#include "Classes/Past.hpp"
#include "Entities/NPC.hpp"
#include "Classes/GameManager.hpp"
#include "Entities/Item.hpp"
#include <memory>
#include <optional>
#include <map>

class Past0 : public Past
{
public:
    void init() override;
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time dt) override;
    void render(sf::RenderWindow& window) override;

private:
    std::optional<Item> draggingItem;
    int draggingFrom = -1;

    std::map<std::string, sf::FloatRect> doorTriggers;
    
    bool m_pendingRoomSwitch = false;
    Room* m_pendingNextRoom = nullptr;
    Room* m_previousRoom = nullptr;  // Para saber de qué habitación venimos
    Pathfinder pathfinder;
    
    bool isDebugPlacing = false;
};