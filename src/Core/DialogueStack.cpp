#include <stack>
#include <unordered_map>
#include <iostream>
#include "Utils/DialogueStack.hpp"
#include "Utils/DialogueSequence.hpp"
#include "Utils/Enums.hpp"
  
// Avanza la línea si es NORMAL, o llama a popDialog si termina.
void DialogueStack::advanceLine() {
    // ... Lógica para avanzar currentLineIndex si es NORMAL
    if (isStackEmpty()) {
        // No hay nada que avanzar.
        return;
    }

    // Usamos 'top()' aquí, confiando en que isStackEmpty() ya fue chequeado.
    const DialogueSequence& currentDialogue = activeDialogues.top();
    
    // La lógica de avance solo aplica a secuencias que no son CHOICE
    if (currentDialogue.getType() != DialogueType::CHOICE) {

        size_t totalLines = currentDialogue.getLines().size();

        currentLineIndex++;
        
        if (currentLineIndex >= totalLines) {
            // La secuencia actual terminó.
            popDialogue();
        }
    }
}

// Devuelve el SceneID a donde se debe saltar si se toma una decisión
std::string DialogueStack::chooseOption(size_t index) {
    
    if (isStackEmpty()) {
        return "";
    }
    
    const DialogueSequence& currentDialogue = activeDialogues.top();
    
    if (currentDialogue.getType() != DialogueType::CHOICE) {
        return "";
    }
    
    // Verificar que el índice sea válido
    if (index >= currentDialogue.options.size()) {
        return "";
    }
    
    std::string nextSceneID = currentDialogue.options[index].nextSceneID;
    
    // Hacer pop del diálogo de elección para continuar con el siguiente
    popDialogue();
    
    return nextSceneID;
}
