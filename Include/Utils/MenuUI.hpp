#pragma once
#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h"
#include "Enums.hpp"


class MenuUI {
private:
    MenuAction m_lastAction = MenuAction::NONE;

    ImFont* m_customFont = nullptr;

    sf::Texture* m_gameLogoTexture = nullptr;

public:
    void render(sf::RenderWindow& window);

    MenuAction getAction() const { return m_lastAction; }

    void setCustomFont(ImFont* fontPtr) { m_customFont = fontPtr; }

    void setGameLogoTexture(sf::Texture* texturePtr) { m_gameLogoTexture = texturePtr; }
};