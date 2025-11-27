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

class StartScene : public GameState
{
public:
    // Constructor y destructor
    StartScene() : dialogueStack(nullptr) {}
    ~StartScene() {}

    void init() override;
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time dt) override;
    void render(sf::RenderWindow& window) override;
    virtual void loadDialogs() override;
    void loadNeighborDialogs();

private:

    DialogueType m_type;
    std::string m_speakerName;
    std::string m_dialogueText;
    bool m_advanceClicked;
    ImFont* m_customFont = nullptr;
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;
    sf::Music m_sceneMusic;

    // Diálogos
    // UI de Diálogos
    DialogueUI dialogueUI;
    bool showDialogue = false;
    // Pila de diálogos (se inicializa en init() con new)
    DialogueStack* dialogueStack;

};