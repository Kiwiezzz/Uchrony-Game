#include "GameStates/MainMenu.hpp"
#include <iostream> 
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include "Core/Game.hpp"
#include "GameStates/Screen1.hpp"
#include "Utils/DialogueUI.hpp"
#include "Utils/Assets.hpp"

void MainMenu::render(sf::RenderWindow& window) {
    
    // Reinicia la acción por defecto
    m_lastAction = MenuAction::NONE;

    if (this->game != nullptr) {     // Verificamos que el jefe exista
        m_customFont = this->game->getFont(); // Le pedimos la fuente
    }

    if (m_customFont) {
        ImGui::PushFont(m_customFont); 
    }

    // --- SETUP DE VENTANA (Dimensiones y Posición) ---
    float window_width = (float)window.getSize().x;
    float window_height = (float)window.getSize().y;
    // Tamaño original de la textura de fondo
    float originalWidth = (float)m_backgroundTexture.getSize().x;
    float originalHeight = (float)m_backgroundTexture.getSize().y;

    // Opción: Mantiene la proporción y cubre toda la ventana (efecto "Cover")
    float scaleX = window_width / originalWidth;
    float scaleY = window_height / originalHeight;
    float scale = std::max(scaleX, scaleY);
        
    // B. APLICAR ESCALA Y CENTRADO A SPRITE DE FONDO
    m_backgroundSprite.setScale(scale, scale);

    // C. Calcular el desplazamiento para centrar la imagen
    float offsetX = (window_width - (originalWidth * scale)) * 0.5f;
    float offsetY = (window_height - (originalHeight * scale)) * 0.5f;

    m_backgroundSprite.setPosition(offsetX, offsetY);
        
    // D. DIBUJAR EL SPRITE
    window.draw(m_backgroundSprite);

    // 1. Definir el TAMAÑO del menú basado en la ventana (Responsive Size)
    // Por ejemplo: El menú ocupa el 75% del ancho y el 80% de la altura de la ventana.
    const float MENU_WIDTH_PERCENT = 1.0f;
    const float MENU_HEIGHT_PERCENT = 1.0f;

    float menuWidth = window_width * MENU_WIDTH_PERCENT;
    float menuHeight = window_height * MENU_HEIGHT_PERCENT;

    // 1. Posicionar la ventana del menú en el centro de la pantalla
    ImGui::SetNextWindowSize(ImVec2(menuWidth, menuHeight));
    ImGui::SetNextWindowPos(
        ImVec2(window_width * 0.5f, window_height * 0.5f), 
        ImGuiCond_Always, 
        ImVec2(0.5f, 0.5f) // Pivote: Centrar el centro de la ventana en el centro de la pantalla
    );

    ImGuiWindowFlags flags = 
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |      
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |    
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground;
    
    ImGui::Begin("Menu", nullptr, flags);

    // --- CÁLCULO DE ESCALADO DE LOGO Y CENTRADO DE CONTENIDO ---
    float contentWidth = ImGui::GetContentRegionAvail().x;
    const float buttonPadding = contentWidth * 0.3f; // Espacio que quieres dejar a los lados
    float buttonWidth = contentWidth - (2.0f * buttonPadding);
    
    float scaledLogoHeight = 0.0f;
    float targetLogoWidth = 0.0f;

    if (m_gameLogoTexture.getNativeHandle() != 0) {
        float originalLogoWidth = (float)m_gameLogoTexture.getSize().x;
        float originalLogoHeight = (float)m_gameLogoTexture.getSize().y;

        // Escalar el logo a 1/3 del ancho disponible en la ventana de ImGui
        targetLogoWidth = contentWidth * (1.0f / 2.0f); 

        // 2. Calcular factor y altura escalada (para mantener la proporción)
        float scaleFactor = targetLogoWidth / originalLogoWidth;
        scaledLogoHeight = originalLogoHeight * scaleFactor;
    }

    // --- 3. CÁLCULO Y APLICACIÓN DEL CENTRADO VERTICAL DEL BLOQUE COMPLETO ---
    const ImGuiStyle& style = ImGui::GetStyle();
    float buttonHeight = (style.FramePadding.y * 2 + ImGui::GetTextLineHeight());
    
    // Altura total del bloque: Logo Escala + (5 Botones * Altura) + (5 Espacios * Altura)
    float totalMenuHeight = scaledLogoHeight + (5 * buttonHeight) + (5 * style.ItemSpacing.y); 

    // Aplicar el offset vertical para centrar el bloque en la ventana de 800x600
    float centerOffsetVertical = (menuHeight - totalMenuHeight) * 0.5f;
    ImGui::SetCursorPosY(centerOffsetVertical); 


    // --- 4. DIBUJO DEL LOGO ---
    if (m_gameLogoTexture.getNativeHandle() != 0) {
        float logoCenterOffset = (contentWidth - targetLogoWidth) * 0.5f;
        ImGui::SetCursorPosX(logoCenterOffset);

        // Dibujar con las dimensiones escaladas
        ImGui::Image(
            (ImTextureID)(uintptr_t)m_gameLogoTexture.getNativeHandle(),
            ImVec2(targetLogoWidth, scaledLogoHeight) 
        );
    

    ImGui::Spacing(); 
    ImGui::Spacing(); // Añadir un segundo espacio
    ImGui::Spacing(); // Añadir un tercer espacioImGui::Spacing(); 

    }

    // --- 5. BOTONES DEL MENÚ ---
    float centerOffsetButtons = (contentWidth - buttonWidth) * 0.5f;

    // Botón Jugar
    ImGui::SetCursorPosX(centerOffsetButtons);
    if (ImGui::Button("Jugar", ImVec2(buttonWidth, 0))) {
    
        m_lastAction = MenuAction::PLAY; 

    // 1. CERRAR LA VENTANA DE IMGUI INICIADA CON ImGui::Begin()
    ImGui::End(); 

    // 2. ¡CRÍTICO! LIMPIAR LA PILA DE FUENTES
        // Esto balancea el ImGui::PushFont() del inicio de render()
    if (m_customFont) {
        ImGui::PopFont(); 
    }

    // 3. CAMBIO DE ESTADO (Destruye el objeto MainMenu, pero ahora está limpio)
    this->game->changeState(new Screen1());

    // 4. Salir: Terminamos la función render() para que no se ejecuten
    //    las líneas de ImGui::End() y PopFont() de más abajo.
    return;

    }
    
    ImGui::Spacing(); // Espaciado

    // Botón Continuar
    ImGui::SetCursorPosX(centerOffsetButtons);
    if (ImGui::Button("Continuar", ImVec2(buttonWidth, 0))) {
        m_lastAction = MenuAction::CONTINUE; 
    }

    ImGui::Spacing(); // Espaciado


    // Botón Opciones
    ImGui::SetCursorPosX(centerOffsetButtons);
    if (ImGui::Button("Opciones", ImVec2(buttonWidth, 0))) {
        m_lastAction = MenuAction::OPTIONS; 
    }

    ImGui::Spacing(); // Espaciado


    // Botón Créditos
    ImGui::SetCursorPosX(centerOffsetButtons);
    if (ImGui::Button("Créditos", ImVec2(buttonWidth, 0))) {
        m_lastAction = MenuAction::CREDITS; 
    }


    ImGui::Spacing(); // Espaciado

    // Botón Salir
    ImGui::SetCursorPosX(centerOffsetButtons);
    if (ImGui::Button("Salir", ImVec2(buttonWidth, 0))) {
        m_lastAction = MenuAction::QUIT; 
        this->game->getWindow().close();
    }

    ImGui::End(); 

    if (m_customFont) {
        ImGui::PopFont();
    }

}

void MainMenu::init() {

    // La función loadFromFile toma la ruta del archivo.
    if (!m_gameLogoTexture.loadFromFile("assets/textures/logo-uchrony.png")) {

        std::cerr << "ERROR: No se pudo cargar el logo 'logo-uchrony.png'.\n";
    }

    // Opcional: si quieres el logo más suave
    m_gameLogoTexture.setSmooth(true);

    if (!m_backgroundTexture.loadFromFile("assets/textures/fondo_menu.png")) {
        // Nota: El escalado lo haremos en la función render
        std::cerr << "ERROR: No se pudo cargar el fondo 'fondo_menu.png'.\n";
    }
    
    m_backgroundSprite.setTexture(m_backgroundTexture);
}

void MainMenu::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Si no procesas eventos, déjalo vacío.
}

void MainMenu::update(sf::Time dt) {
    // Si el menú no tiene lógica de animación o temporizador, déjalo vacío.
}

void MainMenu::loadDialogs() {}

//MenuAction getAction() const { return m_lastAction; /* to do */}

//void setCustomFont(ImFont* fontPtr) { m_customFont = fontPtr; /* to do */}

//void setGameLogoTexture(sf::Texture* texturePtr) { m_gameLogoTexture = texturePtr; /* to do */}