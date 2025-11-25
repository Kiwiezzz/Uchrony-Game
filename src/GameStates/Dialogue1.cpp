#include "GameStates/Dialogue1.hpp"
#include "GameStates/MainMenu.hpp"
#include "../../Include/Core/Game.hpp"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include "Utils/Enums.hpp"
#include <cstdint>

void Dialogue1::render(sf::RenderWindow& window) {

    ImFont* fontPtr = nullptr;

    if (this->game != nullptr) {
        fontPtr = this->game->getFont();
    }

    if (fontPtr) {
        ImGui::PushFont(fontPtr);
    }

    // 1. Calcular la posición y tamaño de la ventana de diálogo (parte inferior)
    float window_width = static_cast<float>(window.getSize().x);
    float window_height = static_cast<float>(window.getSize().y);

    // Altura fija para la caja de diálogo
    float dialogHeight = 150.0f;

    // Establecer posición y tamaño para la próxima ventana de ImGui
    ImGui::SetNextWindowPos(ImVec2(0, window_height - dialogHeight));
    ImGui::SetNextWindowSize(ImVec2(window_width, dialogHeight));

    ImGui::Begin("GameDialogueWindow", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse);

    // Si cargamos una textura para la ventana de diálogo, la dibujamos como fondo
    if (texturaDialogo.getSize().x > 0) {
        ImVec2 winPos = ImGui::GetWindowPos();
        ImVec2 winSize = ImGui::GetWindowSize();

        // sf::Texture::getNativeHandle() devuelve el id nativo de la textura (GLuint en OpenGL)
        ImTextureID texId = (ImTextureID)(uintptr_t)texturaDialogo.getNativeHandle();

        ImGui::GetWindowDrawList()->AddImage(texId,
            ImVec2(winPos.x, winPos.y),
            ImVec2(winPos.x + winSize.x, winPos.y + winSize.y));
    }

    // Contenido del diálogo (texto encima del fondo)
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.95f, 0.95f, 1.0f));
    ImGui::SetCursorPos(ImVec2(16.f, 8.f));
    ImGui::Text("%s:", m_speakerName.c_str());
    ImGui::PopStyleColor();

    ImGui::Separator();

    ImGui::SetCursorPos(ImVec2(16.f, 32.f));
    ImGui::TextWrapped("%s", m_dialogueText.c_str());

    // Botón de avance alineado a la derecha
    float advanceButtonWidth = 120.0f;
    float padding = 10.0f;
    ImGui::SetCursorPosX(ImGui::GetWindowSize().x - advanceButtonWidth - padding);

    if (ImGui::Button("Continuar >", ImVec2(advanceButtonWidth, 0))) {
        m_advanceClicked = true;
    }

    ImGui::End();

    if (fontPtr) {
        ImGui::PopFont();
    }
}

void Dialogue1::init() {
    // Variables iniciales de diálogo
    m_type = DialogueType::NORMAL;
    m_speakerName = "John Barr";
    m_dialogueText = "La mesa está vacía, busca en otro sitio.";
    m_advanceClicked = false;

    // Intentar cargar la textura de la ventana de diálogo.
    // Colocar tu PNG en: assets/textures/dialog_box.png o cambiar la ruta abajo.
    if (!texturaDialogo.loadFromFile("assets/textures/dialog_box.png")) {
        std::cerr << "Warning: no se pudo cargar assets/textures/dialog_box.png (diálogo)" << std::endl;
    }
}

void Dialogue1::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Procesar eventos si es necesario (por ahora vacío)
}

void Dialogue1::update(sf::Time dt) {
    // Lógica de actualización del diálogo si se requiere
}

