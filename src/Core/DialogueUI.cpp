#include "Utils/DialogueUI.hpp"
#include "Utils/Assets.hpp"
#include <cstdint>

// --- Inicialización ---

DialogueUI::DialogueUI() : m_advanceClicked(false) {
    // Inicialización de valores por defecto
    m_speakerName = "Narrador";
    m_dialogueText = "¡Bienvenido a Uchrony Game!";
}

void DialogueUI::init(){

    m_dialogueBoxTexture.new_path_and_update("assets/textures/dialogue_box.png");
    m_texId = (ImTextureID)(uintptr_t)m_dialogueBoxTexture.texture.getNativeHandle();
    
};

// QUEDE POR AQUI

void DialogueUI::render(const sf::RenderWindow& window){

auto ws = window.getSize();
float startYRatio = 0.7f;
float heightRatio = 1.0f - startYRatio;

ImGui::SetNextWindowPos(ImVec2(0, ws.y * startYRatio)); 
ImGui::SetNextWindowSize(ImVec2((float)ws.x, ws.y * heightRatio));

if (ImGui::Begin("D", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove)) {
    // Obtén las dimensiones originales de tu textura
    // Reemplaza esto con el método apropiado según tu librería
    float texWidth = m_dialogueBoxTexture.texture.getSize().x;   // Ejemplo para SFML
    float texHeight = m_dialogueBoxTexture.texture.getSize().y;  // Ejemplo para SFML
    
    float aspectRatio = texWidth / texHeight;
    ImVec2 availSize = ImGui::GetContentRegionAvail();
    
    float displayWidth = availSize.x;
    float displayHeight = displayWidth / aspectRatio;
    
    if (displayHeight > availSize.y) {
        displayHeight = availSize.y;
        displayWidth = displayHeight * aspectRatio;
    }
    
    // Centra la imagen horizontalmente
    ImGui::SetCursorPosX((availSize.x - displayWidth) * 0.5f);
    
    ImGui::Image(m_texId, ImVec2(displayWidth, displayHeight));
    ImGui::End();
}
};

void DialogueUI::renderLinearText(const DialogueLine& line){ };
    
int DialogueUI::renderDecisionPrompt(const std::vector<DialogueSequence::choiceOption>& options){ return -1; };

bool DialogueUI::wasAdvanceClicked(){ return false; };

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