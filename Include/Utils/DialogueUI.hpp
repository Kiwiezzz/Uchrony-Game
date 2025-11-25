#pragma once

#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h"
#include <string>
#include "Include/Utils/Enums.hpp"
#include "Include/Utils/DialogueSequence.hpp"
#include "Include/Utils/DialogueLine.hpp"

class DialogueUI {
private:
    // Necesario para saber si mostrar botón de continuar u opciones.
    DialogueType m_type;
    std::string m_speakerName;
    std::string m_dialogueText;
    bool m_advanceClicked = false;

public:
    DialogueUI() = default;

    // Método principal de dibujo
    // Recibe la secuencia (tope de la pila) y el índice actual.
    // Retorna la opción elegida o -1 si no hubo elección.
    void render(DialogueSequence& sequence, int currentLineIndex);

    void renderLinearText(const DialogueLine& line);
    
    int renderDecisionPrompt(const std::vector<DialogueSequence::DecisionOption>& options);

    // 2. Método para consultar si el usuario hizo clic en "Continuar"
    // Reinicia la bandera a 'false' inmediatamente después de consultarla.
    bool wasAdvanceClicked();
};