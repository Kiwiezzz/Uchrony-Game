#include <stack>
#include <unordered_map>
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

        std::cout << "Avanzando. Índice anterior: " << currentLineIndex - 1 << std::endl;
        currentLineIndex++;
        std::cout << "Nuevo índice: " << currentLineIndex << " / Total de líneas: " << totalLines << std::endl;
        
        if (currentLineIndex >= totalLines) {
        std::cout << "¡Diálogo terminado! POP" << std::endl;
        // La secuencia actual terminó.
        popDialogue(); 
        }
        
    }

}

// Devuelve el SceneID a donde se debe saltar si se toma una decisión
std::string DialogueStack::chooseOption(size_t index) {
    return  "";
        // ... Lógica para elegir la opción y obtener el nextSceneID
}