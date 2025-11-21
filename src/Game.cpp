#include "../Include/Core/Game.hpp" 
#include "imgui-SFML.h"
#include "imgui.h"
#include <iostream>

Game::Game() 
    : m_window(sf::VideoMode(800, 600), "Uchrony Game"), 
      m_currentState(MenuAction::MENU) 
      // (Asegúrate de inicializar todos los miembros que necesitan inicialización)
{
    // Lógica del constructor
    m_window.setFramerateLimit(60);
    initImGui();
}

Game::~Game() {
}

void Game::initImGui() {

    bool success = ImGui::SFML::Init(m_window);
    if (!success) {
        std::cerr << "Failed to initialize ImGui-SFML!" << std::endl;
    }

    // Cargar la textura del logo del juego
    if (!m_logoTexture.loadFromFile("assets/textures/logo-uchrony.png")) {
        std::cerr << "ERROR: No se pudo cargar la textura del logo: assets/textures/logo/logo-uchrony.png" << std::endl;
    }

    ImGuiStyle& style = ImGui::GetStyle();

    // Redondez de la Ventana (para las esquinas del menú)
    style.WindowRounding = 8.0f; 

    // 🚨 CLAVE: Redondez de los Marcos (Botones, campos de texto, etc.)
    // Un valor mayor dará esquinas más redondas. 
    // Para botones completamente redondos, usa un valor grande (ej. 40.0f)
    style.FrameRounding = 20.0f; // Prueba con 12.0f para un redondeo suave

    // Redondez del Botón Activo (cuando se presiona)
    style.GrabRounding = 20.0f;

    style.FramePadding = ImVec2(
        15.0f, // ⬅️ Relleno horizontal: Aumenta el ancho del botón
        12.0f  // ⬆️ Relleno vertical: Aumenta la altura del botón
    );

    // 1. Obtener el objeto ImGuiIO
    ImGuiIO& io = ImGui::GetIO();

    // 2. Definir la ruta a tu archivo .ttf
    const char* fontPath = "assets/textures/fonts/StackSansHeadline-ExtraLight.ttf"; 
    float fontSize = 18.0f; // Tamaño en píxeles

    m_menuUI.setGameLogoTexture(&m_logoTexture);

    // 3. Cargar la fuente. Esto la convierte en la fuente por defecto.
    ImFont* newFont = io.Fonts->AddFontFromFileTTF(fontPath, fontSize);
    
    // 4. Reconstruir el Atlas para que ImGui-SFML pueda usar la fuente
    bool fontUpdateSuccess = ImGui::SFML::UpdateFontTexture(); 

    if (newFont && fontUpdateSuccess) {

    m_menuUI.setCustomFont(newFont);

    std::cout << "Fuente personalizada cargada y asignada." << std::endl;
    
    } else {
        std::cerr << "ADVERTENCIA: Falló la carga de la fuente desde " << fontPath << std::endl;
    }
}

void Game::MySaveFunction() {
    std::cout << "DEBUG: Guardando..." << std::endl;
}

void Game::run()
{
    sf::Clock clock;
    while (m_window.isOpen()) {
        
        // 1. Manejo de Eventos
        sf::Event event;
        while (m_window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(m_window, event);
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
        }

        // 2. Actualizar ImGui (necesario para la interactividad)
        sf::Time dt = clock.restart();
        ImGui::SFML::Update(m_window, dt);

        // 3. Renderizado y UI (Tu lógica de prueba aquí)
        
        m_window.clear(sf::Color(20, 20, 40)); 
        
        // === Ventana de Prueba de ImGui ===
        m_menuUI.render(m_window);
        // ===================================

        // 4. Renderizado final
        ImGui::SFML::Render(m_window);
        m_window.display(); 
    }
    ImGui::SFML::Shutdown();
}

