#pragma once
#include "Core/GameState.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

// COPIAR Y PEGAR ESTA PLANTILLA DE ESCENA PARA CREAR UNA NUEVA
// Recordar: Crear el respectivo .cpp con las definiciones de cada función,
// aquí sólo van firmas.

class PlantillaEscena : public GameState {
private:
    // --- AQUÍ VAN LAS VARIABLES DE LA ESCENA ---

    sf::Texture texturaJugador; // ¡IMPORTANTE! Las texturas deben ser miembros de la clase
    sf::Sprite spriteJugador;
    
    // Si ya tienes clases, pones las instancias aquí:
    // Player jugador;
    // Map mapa;

public:
    
    // --- AQUÍ VAN LAS FUNCIONES DE LA CLASE ---

    void init() override {
        // ¿Qué va aquí? --> Todos los componentes iniciales que se deban cargar
        // antes de la escena como:
        // texturas, setear posiciones iniciales, música, etc.
        if (!texturaJugador.loadFromFile("player.png")) {
            // Mostrar error en caso de no encontrar
            std::cerr << "ERROR: No se pudo cargar la textura 'player.png'.\n";
        }
        spriteJugador.setTexture(texturaJugador);
    }

    void handleEvent(sf::Event& event, sf::RenderWindow& window) override {
        // ¿Qué va aquí? --> Todos los eventos de la escena y cómo se gestionan:
        // Cerrar ventana, teclas que solo se pulsan una vez (Pause, Disparo)
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }

    void update(sf::Time dt) override {
        // ¿Qué va aquí? --> Toda la lógica de movimiento y colisiones:
        // Lo que usaba Keyboard::isKeyPressed() para moverse fluido
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            spriteJugador.move(100 * dt.asSeconds(), 0);
        }
    }

    void render(sf::RenderWindow& window) override {
        // ¿Qué va aquí? --> Toda la lógica de la interfaz con SFML y/o ImGui
        window.draw(spriteJugador);
    }
};