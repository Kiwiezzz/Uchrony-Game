#include "../Include/GameStates/Dialogue1.hpp"
#include "../Include/GameStates/MainMenu.hpp"
#include "../../Include/Core/Game.hpp"
#include "imgui.h" 
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>

void Dialogue1::render(sf::RenderWindow& window) {

    // Usar la fuente

    ImFont* fontPtr;

    if (this->game != nullptr) {     // Verificamos que el jefe exista
        fontPtr = this->game->getFont(); // Le pedimos la fuente
    }

    if (fontPtr) {
        ImGui::PushFont(fontPtr); 
    }
    
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
        //ImGuiWindowFlags_NoBackground | /*OJO esto es para probar transparencia*/
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

    if (fontPtr) {
        ImGui::PopFont();
    }
}

void Dialogue1::init() {
    // Variables iniciales de diálogo
    m_type = DialogType::LINE;
    m_speakerName = "John Barr";
    m_dialogueText = "La mesa está vacía, busca en otro sitio.";
    m_advanceClicked = false;
}

void Dialogue1::handleEvent(sf::Event& event, sf::RenderWindow& window) {
        // Si no procesas eventos, déjalo vacío.
}

void Dialogue1::update(sf::Time dt) {
        // Si no hay lógica de actualización, déjalo vacío.
}

