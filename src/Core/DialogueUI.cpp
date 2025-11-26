#include "Utils/DialogueUI.hpp"
#include "Utils/Assets.hpp"
#include <cstdint>
#include <iostream>

// --- Inicialización ---

DialogueUI::DialogueUI() : game(nullptr), m_advanceClicked(false) {
    // Inicialización de valores por defecto
    m_speakerName = "Narrador";
    m_dialogueText = "¡Bienvenido a Uchrony Game!";
}

void DialogueUI::render(sf::RenderWindow& window, const DialogueSequence& sequence, const std::vector<DialogueSequence::choiceOption>& options, const sf::Font& font, int currentLineIndex)  {

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

    // Altura fija para evitar cambio brusco
    float dialogHeight = 150.0f;

    // Establecer posición y tamaño para la próxima ventana de ImGui
    ImGui::SetNextWindowPos(ImVec2(0, window_height - dialogHeight));
    ImGui::SetNextWindowSize(ImVec2(window_width, dialogHeight));

    ImGui::SetNextWindowBgAlpha(0.0f);

    ImGui::Begin("GameDialogueWindow", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse);

        ImVec2 winPos = ImGui::GetWindowPos();
        ImVec2 winSize = ImGui::GetWindowSize();
        
        // Color Negro (0, 0, 0) con 75% de opacidad (Alpha 191/255)
        ImU32 semiTransparentBlack = IM_COL32(0, 0, 0, 191); 

        // Dibuja un rectángulo relleno que cubre toda la ventana de diálogo
        ImGui::GetWindowDrawList()->AddRectFilled(
            winPos,                                     // Esquina superior izquierda (p_min)
            ImVec2(winPos.x + winSize.x, winPos.y + winSize.y), // Esquina inferior derecha (p_max)
            semiTransparentBlack                        // Color y opacidad
        );

    // Contenido del diálogo (texto encima del fondo)

    const DialogueLine& currentLine = sequence.getLines()[currentLineIndex];
    m_speakerName = currentLine.getSpeakerName();
    m_dialogueText = currentLine.getDialogueText();
    
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.95f, 0.95f, 1.0f));
    ImGui::SetCursorPos(ImVec2(16.f, 8.f));
    ImGui::Text("%s:", m_speakerName.c_str());
    ImGui::PopStyleColor();

    ImGui::Separator();

    // Usar padding horizontal pero dejar que el cursor Y fluya naturalmente
    ImGui::SetCursorPosX(16.f);
    ImGui::TextWrapped("%s", m_dialogueText.c_str());
    ImGui::Spacing();

    // Si hay opciones, renderizarlas
    if (sequence.getType() == DialogueType::CHOICE) {
        if (game) {
            renderOptions(window, sequence, sequence.options, game->getSFMLFont(), currentLineIndex);
        }
    } else {
    // Botón de avance solo para diálogos normales
    float advanceButtonWidth = 120.0f;
    float padding = 10.0f;
    ImGui::SetCursorPosX(ImGui::GetWindowSize().x - advanceButtonWidth - padding);

    if (ImGui::Button("Continuar >", ImVec2(advanceButtonWidth, 0))) {
        m_advanceClicked = true;
    }
    }

    ImGui::End(); // <-- Este End() cierra la única ventana

    // Pop the font AFTER ending the window
    if (fontPtr) {
        ImGui::PopFont();
    }
}

void DialogueUI::init() {
    // Variables iniciales de diálogo
    //m_type = DialogueType::NORMAL;
    //m_speakerName = "John Barr";
    //m_dialogueText = "La mesa está vacía, busca en otro sitio.";
    m_advanceClicked = false;

    // para que ImGui no tenga bordes redondeados ni transparencia
    ImGui::GetStyle().Alpha = 1.0f;
    ImGui::GetStyle().WindowRounding = 0.0f;
}

void DialogueUI::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Procesar eventos si es necesario (por ahora vacío)
}

void DialogueUI::update(sf::Time dt) {
    // Lógica de actualización del diálogo si se requiere
}

void DialogueUI::renderLinearText(const DialogueLine& line){ };
    
int DialogueUI::renderDecisionPrompt(const std::vector<DialogueSequence::choiceOption>& options){ return -1; };

bool DialogueUI::wasAdvanceClicked(){
    if (m_advanceClicked) {
            m_advanceClicked = false; // CONSUMIR EL CLICK AQUÍ
            return true;
        }
    return false;
};

int DialogueUI::getChosenOption(){
    int result = m_chosenOptionIndex;
    m_chosenOptionIndex = -1; // Resetear después de leer
    return result;
}

void DialogueUI::renderOptions(sf::RenderWindow& window, const DialogueSequence& sequence, const std::vector<DialogueSequence::choiceOption>& options, const sf::Font& font, int currentLineIndex) 
{
    const DialogueLine& currentLine = sequence.getLines()[currentLineIndex];
            
        float availableWidth = ImGui::GetContentRegionAvail().x;

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        for (size_t i = 0; i < options.size(); ++i) {
            ImGui::PushID(i); 
            
            if (ImGui::Button(options[i].optionText.c_str(), ImVec2(availableWidth, 0))) {
                m_chosenOptionIndex = static_cast<int>(i);
                m_advanceClicked = true;
            }
            
            ImGui::PopID(); 
            ImGui::Spacing();
        }
}