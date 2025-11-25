#include <stack>
#include <unordered_map>
#include "Utils/DialogueStack.hpp"

class DialogManager {
private:
    // Pila para las líneas de diálogo que esperan ser mostradas
    std::stack<DialogueStack> m_dialogStack;
    
    // Almacena todos los bloques de diálogo del juego (usualmente cargado de un archivo)
    std::unordered_map<int, std::vector<DialogueStack>> m_dialogBlocks;

public:

    // ====== Métodos de renderizado de diálogo generales: ======

    void renderDialogs();

    void renderLinearText();

    void renderDecisionPrompt();

    void advanceLine();
public:

    // ====== Métodos de renderizado de diálogo generales: ======

    void renderDialogs();

    void renderLinearText();

    void renderDecisionPrompt();

    void advanceLine();
};