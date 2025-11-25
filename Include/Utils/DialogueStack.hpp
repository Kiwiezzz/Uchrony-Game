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
    std::stack<DialogueSequence> activeDialogs;
    
    // Índice actual para secuencias NORMAL
    int currentLineIndex = 0;
    
    DialogueUI ui;

    Game& game;

public:
    DialogueStack(Game& game) : game(game) {}

    // Métodos de la Pila (Interfaz LIFO)
    void pushDialog(const DialogueSequence& dialog) {
        activeDialogs.push(dialog);
        currentLineIndex = 0; // Reiniciar índice al empezar una nueva secuencia
    }

    // Elimina el diálogo tope de la pila
    void popDialog() {
        if (!activeDialogs.empty()) {
            activeDialogs.pop();
        }
    }

    // Consulta si la pila está vacía
    bool isStackEmpty() const {
        return activeDialogs.empty();
    }
    
    // Métodos para el flujo del diálogo actual
    const DialogueSequence& getCurrentDialog() const {
        // Asume que la pila no está vacía antes de llamar
        return activeDialogs.top();
    }
    
    // Avanza la línea si es NORMAL, o llama a popDialog si termina.
    void advanceLine();

    // Devuelve el SceneID a donde se debe saltar si se toma una decisión
    std::string chooseOption(size_t index);
};