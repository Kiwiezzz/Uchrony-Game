#pragma once

#include <vector>
#include <stack>
#include <string>
#include "Utils/Enums.hpp"
#include "Utils/DialogueSequence.hpp"
#include "Utils/DialogueUI.hpp"
#include "Core/Game.hpp"

class DialogueStack {
private:
    // La pila para gestionar el orden de los diálogos
    std::stack<DialogueSequence> activeDialogues;
    
    // Índice actual para secuencia NORMAL
    int currentLineIndex = 0;
    
    DialogueUI ui;

    Game& game;

public:

    // Constructor
    DialogueStack(Game& g) : game(g) {  
        // El cuerpo del constructor puede estar vacío si no hay más lógica
    }

    // Métodos de la Pila (Interfaz LIFO)
    void pushDialogue(const DialogueSequence& dialogue) {
        activeDialogues.push(dialogue);
        currentLineIndex = 0; // Reiniciar índice al empezar una nueva secuencia
    }

    void popDialogue() {
        if (!activeDialogues.empty()) {
            activeDialogues.pop();
        }
    }

    bool isStackEmpty() const {
        return activeDialogues.empty();
    }
    
    // Métodos para el flujo del diálogo actual
    const DialogueSequence& getCurrentDialogue() {
        return activeDialogues.top();
    }

    const DialogueLine& getCurrentLine() {
        return getCurrentDialogue().dialogueLines[currentLineIndex];
    }

    int getCurrentLineIndex() {
        return currentLineIndex;
    }
    
    // Avanza la línea si es NORMAL, o llama a popDialog si termina.
    void advanceLine();

    // Devuelve el SceneID a donde se debe saltar si se toma una decisión
    std::string chooseOption(size_t index);
};