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

class Past0 : public Past
{
public:
    // Constructor y destructor
    Past0() : dialogueStack(nullptr) {}
    ~Past0() { if (dialogueStack) delete dialogueStack; }

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
    sf::Time m_npcAnimationTimer;

    // Diálogos
    // UI de Diálogos
    DialogueUI dialogueUI;
    bool showDialogue = false;
    // Pila de diálogos (se inicializa en init() con new)
    DialogueStack* dialogueStack;
};