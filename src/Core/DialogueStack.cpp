#include <stack>
#include <unordered_map>
#include "Utils/DialogueStack.hpp"
#include "Utils/DialogueSequence.hpp"
  
// Avanza la línea si es NORMAL, o llama a popDialog si termina.
void advanceLine() {
        // ... Lógica para avanzar currentLineIndex si es NORMAL
}

// Devuelve el SceneID a donde se debe saltar si se toma una decisión
std::string chooseOption(size_t index) {
    return  "";
        // ... Lógica para elegir la opción y obtener el nextSceneID
}