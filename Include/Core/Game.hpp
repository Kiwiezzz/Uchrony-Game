#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Core/GameState.hpp"
#include "GameStates/Screen1.hpp"

class Game
{
private:
    sf::RenderWindow window;
    sf::Clock clock;
    GameState* currentState;

public:
    Game();

    ~Game();

    /// @brief Función para cambiar de nivel desde cualquier lado
    /// @param newScene 
    void changeState(GameState* newState);

    void run();

};