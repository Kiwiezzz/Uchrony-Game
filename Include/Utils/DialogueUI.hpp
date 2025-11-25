#pragma once

#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h"
#include <string>

class DialogueUI {
private:
    std::string m_speakerName;
    std::string m_dialogueText;
    bool m_advanceClicked = false;

public:
    DialogueUI();

    // Configura el texto a mostrar
    void setText(const std::string& speaker, const std::string& text);

    // Dibuja la ventana de diálogo usando ImGui
    void render(sf::RenderWindow& window);

    // Retorna true si el usuario pulsó "Continuar"
    bool canAdvance();
};