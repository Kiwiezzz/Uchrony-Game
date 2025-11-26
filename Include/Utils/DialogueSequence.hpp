#pragma once
#include <string>
#include <vector>
#include "Utils/Enums.hpp"
#include "Utils/DialogueLine.hpp"

/// @brief Representa una secuencia de lineas de diálogo y opciones en el juego.
class DialogueSequence {
private:
    DialogueType type;

public:
    // Estructura para opciones de decisión (Usado para CHOICE).
    struct choiceOption {
        // Ir al siguiente diálogo
        std::string optionText;
        // Ir a la siguiente escena
        // La clave aquí: indica a qué SceneID/NodeID debe pasar el juego.
        std::string nextSceneID;
    };
    
    std::vector<choiceOption> options;

    // Vector de cada persona y su linea de diálogo
    std::vector<DialogueLine> dialogueLines;

    DialogueType getType() const { return type; }
    
    const std::vector<DialogueLine>& getLines() const { return dialogueLines; }
    
    DialogueSequence(DialogueType t) : type(t) {}
};