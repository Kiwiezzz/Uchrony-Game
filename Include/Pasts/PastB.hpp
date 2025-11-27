#pragma once

#include "Classes/Past.hpp"
#include "Entities/NPC.hpp"
#include "Classes/GameManager.hpp"
#include "Entities/Item.hpp"
#include "Utils/DialogueUI.hpp"
#include "Utils/DialogueStack.hpp"
#include <memory>
#include <optional>
#include <map>

class PastB : public Past
{
public:
    // Constructor y destructor
    PastB() {}
    ~PastB() {}

    bool approachEntity(const NavGrid& navGrid, Vec2f targetPos, float stopDistance);
    void init() override;
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time dt) override;
    void render(sf::RenderWindow& window) override;
    virtual void loadDialogs() override;

private:

    std::optional<Item> draggingItem;
    int draggingFrom = -1;

    std::map<std::string, sf::FloatRect> doorTriggers;
    
    bool m_pendingRoomSwitch = false;
    Room* m_pendingNextRoom = nullptr;
    Room* m_previousRoom = nullptr;
    Pathfinder pathfinder;
    
    // Sistema de debug
    bool isDebugPlacing = false;
    sf::Sprite* debugSprite = nullptr;  // Sprite siendo posicionado
    std::string debugSpriteName = "";   // Nombre del sprite

    // Diálogos
    // UI de Diálogos
    DialogueUI dialogueUI;
    bool showDialogue = false;
    // Pila de diálogos (se inicializa en init() con new)
    std::unique_ptr<DialogueStack> dialogueStack;
};