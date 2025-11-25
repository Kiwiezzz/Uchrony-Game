#include "Utils/DialogueUI.hpp"

// --- Inicialización ---

DialogueUI::DialogueUI() : m_advanceClicked(false) {
    // Inicialización de valores por defecto
    m_speakerName = "Narrador";
    m_dialogueText = "¡Bienvenido a Uchrony Game!";
}

void render(DialogueSequence& sequence, int currentLineIndex){};

void renderLinearText(const DialogueLine& line){};
    
int renderDecisionPrompt(const std::vector<DialogueSequence::choiceOption>& options){};

bool wasAdvanceClicked(){};


// --- Renderizado con ImGui OLD---
/*
void DialogueUI::render(sf::RenderWindow& window) {
    
    // 1. Calcular la posición y tamaño de la ventana de diálogo (parte inferior)
    float window_width = (float)window.getSize().x;
    float window_height = (float)window.getSize().y;
    
    // Altura fija para la caja de diálogo (ejemplo: 150 píxeles de alto)
    float dialogHeight = 150.0f; 

    // 2. Establecer la posición y tamaño para la próxima ventana de ImGui
    ImGui::SetNextWindowPos(ImVec2(0, window_height - dialogHeight));
    ImGui::SetNextWindowSize(ImVec2(window_width, dialogHeight));

    // 3. Iniciar la ventana del diálogo
    ImGui::Begin("GameDialogueWindow", nullptr, 
        ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoCollapse | 
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse);
        
    // 4. Contenido del diálogo
    
    // Nombre del personaje
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.8f, 0.0f, 1.0f)); // Color amarillo/dorado
    ImGui::Text("%s:", m_speakerName.c_str());
    ImGui::PopStyleColor();

    ImGui::Separator();
    
    // El texto real del diálogo (TextWrapped es crucial para que salte de línea)
    ImGui::TextWrapped("%s", m_dialogueText.c_str());

    // 5. Botón/Indicador de Avance
    
    // Colocamos el botón en la esquina inferior derecha (o simplemente alineado a la derecha)
    float advanceButtonWidth = 80.0f;
    float padding = 10.0f;
    ImGui::SetCursorPosX(ImGui::GetWindowSize().x - advanceButtonWidth - padding);
    
    if (ImGui::Button("Continuar >", ImVec2(advanceButtonWidth, 0))) {
        // Establecemos el flag que será leído por DialogueManager::update()
        m_advanceClicked = true; 
    }

    ImGui::End();
}
    
*/