#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

// Incluir las clases que gestionaremos y usaremos
#include "DialogueLine.hpp" 
#include "DialogueUI.hpp" 
#include "Core/Game.hpp" // Para usar el enum Game::State

class DialogueManager {
private:
    // 1. Datos: El árbol de diálogo actual
    DialogueTree m_currentDialogue;
    
    // 2. UI: La clase que dibuja la ventana
    DialogueUI m_ui;

    // 3. Estado del flujo de la historia
    int m_currentNodeID;
    
    // Referencia al juego principal para cambiar el estado
    //Game& game; 

public:
    // Constructor (necesita una referencia al juego)
    //DialogueManager(Game& game);
    
    // Métodos principales para el bucle del juego
    void update(sf::Time dt);
    void render(sf::RenderWindow& window);

    // Métodos de control
    void startDialogue(const std::string& treeName); // Carga y comienza un diálogo (ej: "intro_mission")
    void advanceDialogue(); // Mueve al siguiente nodo
    
    bool isDialogueActive() const; // Comprueba si el estado es DIALOGUE
};

class DialogueRender {
    
private:
    // Pila para las líneas de diálogo que esperan ser mostradas
    std::stack<DialogueData> m_dialogStack;
    
    // Almacena todos los bloques de diálogo del juego (usualmente cargado de un archivo)
    std::unordered_map<int, std::vector<DialogueData>> m_dialogBlocks;

public:

    // ====== Métodos de renderizado de diálogo generales: ======

    void renderDialogs();

    void renderLinearText();

    void renderDecisionPrompt();

    void advanceLine();
};