/*#pragma once
#include <string>
#include <vector>
#include "Utils/Enums.hpp"
#include "Utils/DialogueLine.hpp"


class DialogueSequence {
private:
    DialogueType type;
    std::vector<DialogueLine> lines;

public:
    // Estructura para opciones de decisión (Usado para CHOICE).
    struct choiceOption {
        std::string text;
        // La clave aquí: indica a qué SceneID/NodeID debe pasar el juego.
        std::string nextSceneID;
    };
    
    std::vector<choiceOption> options;

    DialogueSequence(DialogueType t) : type(t) {}
};*/