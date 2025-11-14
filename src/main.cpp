#include <iostream>
#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h" 
#include "Core/Game.hpp"


int main() {
   // Game game; // Crea la instancia del juego
   // game.run(); // Inicia el bucle principal
    std::cout << "Uchrony Game iniciado!" << std::endl;

    
    // --- MISSING DECLARATIONS ---
    
    // 1. Declare and Initialize the Render Window (referred to by 'window')
    sf::RenderWindow window(sf::VideoMode(800, 600), "Uchrony Game");
    window.setFramerateLimit(60); // Optional, but good practice

    sf::RectangleShape shape(sf::Vector2f(400.f, 100.f)); 
    
    // 3. Initialize ImGui-SFML (must be called after the window is created)
    // This is required before calling Update, Render, or Shutdown.
    bool success = ImGui::SFML::Init(window);
    if (!success) {
        std::cerr << "Failed to initialize ImGui-SFML!" << std::endl;
        return -1; // Exit if initialization fails
    }

    // Now, the shape is correctly declared before its methods are called
    shape.setFillColor(sf::Color(204, 77, 5));
    shape.setPosition(200, 200);
    
    sf::Clock deltaClock;

    // The main loop can now use 'window.isOpen()'
    while (window.isOpen())
    {
        sf::Event event;
        // The event loop can now use 'window.pollEvent()'
        while(window.pollEvent(event))
        {
            // ImGui is now initialized
            ImGui::SFML::ProcessEvent(event);
            if(event.type == sf::Event::Closed)
            // 'window.close()' is valid
            window.close();
        }
        // ImGui Update is valid
        ImGui::SFML::Update(window, deltaClock.restart());

        // 'window' methods are valid
        window.clear(sf::Color(18, 33, 43));
        // 'window.draw(shape)' is valid
        window.draw(shape);
        // ImGui Render is valid
        ImGui::SFML::Render(window);
        window.display();
    }
    
    // ImGui Shutdown is valid
    ImGui::SFML::Shutdown();
    return 0;
}