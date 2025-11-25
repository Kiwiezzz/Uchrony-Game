#pragma once
#include <SFML/Graphics.hpp>

class Game;

class GameState {
protected:
    Game* game; //El numero de mi jefe

public:
    virtual ~GameState(){}

    void setGame(Game* gamePtr) {
        this->game = gamePtr;
    }

    virtual void init() = 0;

    /// @brief Se encarga de manejar los eventos (inputs) que suceden.
    /// Es para cambiar cosas por voluntad del jugador.
    virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;

    /// @brief Es para actualizar cosas automaticamente
    /// Es para cambiar cosas por el paso de tiempo
    /// @param dt 
    virtual void update(sf::Time dt) = 0;

    /// @brief Es para dibujar esas cosas en la ventana
    /// @param window 
    virtual void render(sf::RenderWindow& window) = 0;

};