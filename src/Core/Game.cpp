#include "Core/Game.hpp"

Game::Game() {
    window.create(sf::VideoMode(800, 600), "Uchrony");
    window.setFramerateLimit(60);
    currentState = nullptr;
}

Game::~Game() {
    // Limpiar la memoria al cerrar el juego
    if (currentState != nullptr) {
        delete currentState;
    }
}

/// @brief Función para cambiar de nivel desde cualquier lado
void Game::changeState(GameState* newScene) {
    if (currentState != nullptr) {
        delete currentState;
    }
    currentState = newScene;
    
    currentState->setGame(this); 

    currentState->init();
}

void Game::run() {
    // Loop principal del juego (Game Loop)
    while (window.isOpen()) {
        // 1. Calcular Delta Time (dt)
        sf::Time dt = clock.restart();

        // 2. Procesar Eventos (Input)
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (currentState != nullptr)
            currentState->handleEvent(event, window);
        }

        // 3. Actualizar (Update)
        if (currentState != nullptr)
        currentState->update(dt);

        // 4. Dibujar (Draw)
        window.clear();
        if (currentState != nullptr)
        currentState->render(window);

        window.display();
    }
}