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

    // ===== Métodos virtuales de cada escena: =====

    virtual void init() = 0;

    /// @brief Se encarga de manejar los eventos (inputs) que suceden.
    /// Es para cambiar cosas por voluntad del jugador.
    /// @param event El evento a gestionar.
    /// @param window La ventana donde se dibuja.
    virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;

    /// @brief Sirve para actualizar cosas automáticamente
    /// Es para cambiar cosas por el paso de tiempo (involuntatiamente).
    /// @param dt El tiempo transcurrido desde la última actualización.
    virtual void update(sf::Time dt) = 0;

    /// @brief Sirve para dibujar todo en las escenas.
    /// @param window La ventana donde se dibuja.
    virtual void render(sf::RenderWindow& window) = 0;

    /// @brief Sirve para cargar todos los diálogos de la escena.
    virtual void loadDialogs() = 0;
};