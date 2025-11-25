#include "Utils/DialogueUI.hpp"
#include "Utils/Assets.hpp"
#include <cstdint>

// --- Inicialización ---

DialogueUI::DialogueUI() : m_advanceClicked(false) {
    // Inicialización de valores por defecto
    m_speakerName = "Narrador";
    m_dialogueText = "¡Bienvenido a Uchrony Game!";
}

// QUEDE POR AQUI

void DialogueUI::render(const sf::RenderWindow& window) {

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

void DialogueUI::init() {
    // Variables iniciales de diálogo
    m_type = DialogueType::NORMAL;
    m_speakerName = "John Barr";
    m_dialogueText = "La mesa está vacía, busca en otro sitio.";
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

bool DialogueUI::wasAdvanceClicked(){ return false; };