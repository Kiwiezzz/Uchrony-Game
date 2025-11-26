#pragma once
#include "Core/GameState.hpp"
#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h"
#include "../Include/Utils/Enums.hpp"

class MainMenu : public GameState {

private:

    MenuAction m_lastAction = MenuAction::NONE;

    ImFont* m_customFont = nullptr;

    sf::Texture m_gameLogoTexture;

public:
    
    void init() override;

    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;

    void update(sf::Time dt) override;

    void render(sf::RenderWindow& window) override;

    void loadDialogs() override;
};