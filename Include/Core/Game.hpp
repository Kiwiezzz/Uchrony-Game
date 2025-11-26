#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Core/GameState.hpp"
#include "GameStates/MainMenu.hpp"
#include "Classes/PastTree.hpp"

class Game
{
private:
    sf::RenderWindow window;
    sf::Clock clock;
    GameState* currentState = nullptr;
    ImFont* m_Font = nullptr;

public:
    Game();

    ~Game();

    /// @brief Función para cambiar de nivel desde cualquier lado
    /// @param newScene 
    void changeState(GameState* newState);

    // En Game.cpp

// Esta función recibe un ID (del mapa) y te devuelve el Objeto real (Pesado)
    GameState* newPastByID(PastID id);

    ImFont* getFont() const { return m_Font; }

    void run();

    sf::RenderWindow& getWindow() { return window; }
};