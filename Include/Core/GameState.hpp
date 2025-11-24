#pragma once
#include <SFML/Graphics.hpp>

class Game;

class GameState {
protected:
    Game* game; //El numero de mi jefe

private:
    sf::RenderWindow window;

public:
    virtual ~GameState(){}

    void setGame(Game* gamePtr) {
        this->game = gamePtr;
    }

    virtual void init() = 0;

    virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;

    virtual void update(sf::Time dt) = 0;

    virtual void render(sf::RenderWindow& window) = 0;

    sf::RenderWindow& getWindow() { return window; }
};