#pragma once

#include <SFML/Graphics.hpp>
#include "../Utils/DialogueManager.hpp" // Incluimos el Manager

class Game {
public:
    // 1. Definir los posibles estados del juego (Crucial para el control)
    enum State {
        MENU,
        PLAYING,
        DIALOGUE, // Nuevo estado
        PAUSED,
        EXITING
    };

private:
    sf::RenderWindow m_window;
    State m_currentState;
    
    // 2. Instancia del DialogueManager. Lo declaramos como puntero 
    // o lo inicializamos en el constructor. Si lo inicializamos aquí,
    // necesitamos el constructor de DialogueManager que acepta 'Game&'.
    DialogueManager m_dialogueManager;

    // 3. Inicialización de SFML/ImGui
    void initImGui();

public:
    Game();
    ~Game();

    void run(); // El bucle principal

    // Métodos para que DialogueManager pueda interactuar
    State getCurrentState() const { return m_currentState; }
    void setState(State newState) { m_currentState = newState; }
};