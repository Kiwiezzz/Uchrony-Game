#pragma once

#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h"
#include <string>
#include "Utils/Enums.hpp"
#include "Utils/DialogueSequence.hpp"
#include "Utils/DialogueLine.hpp"
#include "Utils/Assets.hpp"

class DialogueUI {
private:
    // Necesario para saber si mostrar botón de continuar u opciones.
    DialogueType m_type;
    std::string m_speakerName;
    std::string m_dialogueText;
    bool m_advanceClicked = false;
    TextureAsset m_dialogueBoxTexture;
    bool showDialogue = false;
    // Referencia en memoria de nuestra imagen
    ImTextureID m_texId = nullptr;

public:

    DialogueUI();

    void init();    

    // DEBE SER ASI
    //void render(DialogueSequence& sequence, int currentLineIndex);

    void render(const sf::RenderWindow& window);

    void renderLinearText(const DialogueLine& line);

    // Método principal de dibujo
    // Recibe la secuencia (tope de la pila) y el índice actual.
    // Retorna la opción elegida o -1 si no hubo elección.
    int renderDecisionPrompt(const std::vector<DialogueSequence::choiceOption>& options);

    // 2. Método para consultar si el usuario hizo clic en "Continuar"
    // Reinicia la bandera a 'false' inmediatamente después de consultarla.
    bool wasAdvanceClicked();
};