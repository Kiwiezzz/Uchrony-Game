// Include/Utils/DialogueUI.hpp

#pragma once

#include <SFML/Graphics.hpp>
#include "../../vendor/imgui-sfml/imgui-SFML.h"
#include "../../vendor/imgui/imgui.h"
#include <string>

class DialogueUI {
private:
    std::string m_speakerName;
    std::string m_dialogueText;
    bool m_advanceClicked;

public:
    DialogueUI();

    // Dibuja la ventana y el texto de ImGui
    void render(sf::RenderWindow& window);

    // Método llamado por el DialogueManager para cambiar el texto
    void setText(const std::string& speaker, const std::string& text);

    // Método para ser llamado por el DialogueManager en update()
    bool canAdvance();
};