/*#include "../Include/Core/Game.hpp"

// Constructor: Inicializa la ventana y el DialogueManager
Game::Game() 
    : m_window(sf::VideoMode(800, 600), "Uchrony Game"), 
      m_currentState(State::MENU),
      //m_dialogueManager(*this) // Pasa 'this' (el objeto Game) por referencia al Manager
{
    m_window.setFramerateLimit(60);
    initImGui();
    
    // Nota: Aquí podrías iniciar un diálogo de bienvenida inmediatamente
    // m_dialogueManager.startDialogue("intro"); 
}

// Inicialización de ImGui (como lo tenías en main.cpp)
void Game::initImGui() {
    bool success = ImGui::SFML::Init(m_window);
    if (!success) {
        std::cerr << "Failed to initialize ImGui-SFML!" << std::endl;
    }
}

// Bucle principal del juego
void Game::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        
        // 1. Manejo de Eventos (SFML)
        sf::Event event;
        while (m_window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(m_window, event);
            if (event.type == sf::Event::Closed || m_currentState == State::EXITING) {
                m_window.close();
            }
            // ... otros eventos ...
        }

        // 2. Actualizar el tiempo de ImGui
        sf::Time dt = clock.restart();
        ImGui::SFML::Update(m_window, dt);

        // 3. Lógica de Actualización (Update)
        m_dialogueManager.update(); // El Manager verifica si el usuario hizo clic
        
        // 4. Renderizado
        m_window.clear(sf::Color(20, 20, 40)); // Fondo
        
        // Renderizado del juego normal (solo si no estamos en diálogo)
        if (m_currentState != State::DIALOGUE && m_currentState != State::MENU) {
            // Dibuja sprites, mapas, etc. (la parte visual del juego)
        }
        
        // Renderizado de la UI
        if (m_currentState == State::DIALOGUE || m_currentState == State::MENU) {
            // El Manager llama a DialogueUI::render()
            m_dialogueManager.render(m_window); 
            // O dibujar el menú de inicio aquí usando ImGui::Begin...
        }

        // Renderizado final de ImGui
        ImGui::SFML::Render(m_window);

        m_window.display();
    }
    ImGui::SFML::Shutdown();
}

*/