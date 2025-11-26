#include "Core/Game.hpp"
#include <iostream>
#include <filesystem>
#include "Pasts/Past0.hpp"
#include "Classes/GameManager.hpp"

Game::Game() {
    window.create(sf::VideoMode(800, 600), "Uchrony Game");

    // Inicializar ImGui-SFML
    auto success = ImGui::SFML::Init(window);

    if (!success) {
    // Si la inicialización falla, cierra la aplicación o lanza una excepción.
    std::cerr << "ERROR: Failed to initialize ImGui-SFML.\n";
    // window.close(); // Si la ventana está abierta
    // Lanza una excepción o realiza un manejo de errores fatal
    }

    // 2. Definir el Estilo (Esto SÍ va aquí)
    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding = 10.0f; 
    style.WindowRounding = 0.0f;
    // Color de botones
    style.Colors[ImGuiCol_Button] = ImVec4(0.306f, 0.200f, 0.000f, 1.0f);
    // Color de fondo
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.725f, 0.576f, 0.353f, 1.0f);
    // 3. Cargar Fuentes (Esto también va aquí)

    m_Font = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/textures/fonts/StackSansHeadline-Medium.ttf", 16.0f);

    if (m_Font == nullptr) {
    std::cerr << "ERROR: No se pudo cargar la fuente. Verifica la ruta.\n";}

    // Actualizar la textura de la fuente
    auto fontTexture = ImGui::SFML::UpdateFontTexture();

    if(!fontTexture){
        std::cerr << "ERROR: No se pudo cargar la fuente. Verifica la ruta.\n";
    }

    if (!m_SFMLFont.loadFromFile("assets/textures/fonts/StackSansHeadline-Medium.ttf")) {
        // Si el archivo no se encuentra o no se puede cargar:
        std::cerr << "ERROR FATAL: No se pudo cargar la fuente de SFML. Verifica la ruta." << std::endl;
        // Detener el programa para evitar el Segmentation Fault
        exit(EXIT_FAILURE); 
    }

    window.setFramerateLimit(60);
    currentState = nullptr;
}

Game::~Game() {
    // Limpiar la memoria al cerrar el juego
    if (currentState != nullptr) {
        delete currentState;
    }

    // Limpiar los recursos de ImGui-SFML
    ImGui::SFML::Shutdown();
}

/// @brief Función para cambiar de nivel desde cualquier lado
void Game::changeState(GameState* newScene) {
    if (currentState != nullptr) {
        delete currentState;
    }
    currentState = newScene;
    
    currentState->setGame(this); 

    currentState->init();
}

void Game::run() {
    // Loop principal del juego (Game Loop)
    while (window.isOpen()) {
        // 1. Calcular Delta Time (dt)
        sf::Time dt = clock.restart();

        // clock de imgui
        sf::Clock imguiClock;

        // 2. Procesar Eventos (Input)
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Procesar eventos de imgui
            ImGui::SFML::ProcessEvent(window, event);
            
            if (currentState != nullptr)
            currentState->handleEvent(event, window);

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    // Usamos dynamic_cast para asegurarnos de que NO estamos ya en el MainMenu.
                    // Esto evita recrear el estado innecesariamente si el usuario ya está allí.
                    if (dynamic_cast<MainMenu*>(currentState) == nullptr) {
                        changeState(new MainMenu());
                    }
                    // Si cambias el estado, el evento no debe ser procesado por el estado anterior.
                    continue; 
                }
            }
        }

        // Abrir el menu si se presiona la tecla Escape

        // 3. Actualizar (Update)
        if (currentState != nullptr)
        currentState->update(dt);
        ImGui::SFML::Update(window, imguiClock.restart()); // actualizar imgui

        // 4. Dibujar (Draw)
        window.clear();

        if (currentState != nullptr)
        currentState->render(window);
        ImGui::SFML::Render(window); // renderizar imgui

        window.display();
    }
}



GameState* Game::newPastByID(PastID id) {
    // Sistema antiguo: cada escena tiene su propia clase
    
    if (id == "PAST_0_ROOM_1") {
        return new Past0();
    }
    else if (id == "SCREEN_1") {
        //return new Screen1();
    }
    // Agrega aquí más escenas según las necesites
    
    std::cerr << "ERROR: Escena no encontrada: " << id << std::endl;
    return nullptr;
}
