#pragma once
#include "Core/GameState.hpp"
#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h"
#include "../Include/Utils/Enums.hpp"

// Incluye aquí tus clases de Jugador, Enemigo, Mapa, etc.

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

};

/*  ANTIGUAS FUNCIONES DE MAIN MENU ROSA

class MenuUI {

public:
    void render(sf::RenderWindow& window);

    MenuAction getAction() const { return m_lastAction; }

    void setCustomFont(ImFont* fontPtr) { m_customFont = fontPtr; }

    void setGameLogoTexture(sf::Texture* texturePtr) { m_gameLogoTexture = texturePtr; }
};*/