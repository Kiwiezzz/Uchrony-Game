#include <iostream>

#pragma once

#include "Core/GameState.hpp"
#include "Classes/GameManager.hpp"
#include "Utils/DialogueUI.hpp"
#include "Utils/DialogueStack.hpp"
#include "Classes/Room.hpp"
#include <memory>
#include <optional>
#include <map>

class loco3 : public GameState
{
public:
    // Constructor y destructor
    loco3() : dialogueStack(nullptr) {}
    ~loco3() {
        if (dialogueStack) {
            delete dialogueStack;
            dialogueStack = nullptr;
        }
    }

    void init() override;
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time dt) override;
    void render(sf::RenderWindow& window) override;
    virtual void loadDialogs() override;
    void loadNeighborDialogs();

private:

    bool m_advanceClicked = false;
    ImFont* m_customFont = nullptr;
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;
    sf::Music m_sceneMusic;
    bool showDialogue = true;

    // Diálogos
    // UI de Diálogos
    DialogueUI dialogueUI;
    // Pila de diálogos (se inicializa en init() con new)
    DialogueStack* dialogueStack;

};
