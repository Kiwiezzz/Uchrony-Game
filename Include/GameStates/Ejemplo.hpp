#pragma once
#include "Core/GameState.hpp"
#include <SFML/Graphics.hpp>
// Incluye aquí tus clases de Jugador, Enemigo, Mapa, etc.

class EscenaJuego : public GameState {
private:
    // --- AQUÍ VAN LAS VARIABLES QUE ANTES ESTABAN SUELTAS EN EL MAIN ---
    sf::Texture texturaJugador; // ¡IMPORTANTE! Las texturas deben ser miembros de la clase
    sf::Sprite spriteJugador;
    
    // Si ya tienes clases, pones las instancias aquí:
    // Player jugador;
    // Map mapa;

public:
    
    
    void init() override {
        // AQUÍ VA LO QUE ESTABA ANTES DEL WHILE(WINDOW.ISOPEN())
        // Cargar texturas, setear posiciones iniciales, música, etc.
        if (!texturaJugador.loadFromFile("player.png")) {
            // Error
        }
        spriteJugador.setTexture(texturaJugador);
    }

    void handleEvent(sf::Event& event, sf::RenderWindow& window) override {
        // AQUÍ VA LO QUE ESTABA DENTRO DEL WHILE(POLL EVENT)
        // Cerrar ventana, teclas que solo se pulsan una vez (Pause, Disparo)
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }

    void update(sf::Time dt) override {
        // AQUÍ VA LA LÓGICA DE MOVIMIENTO Y COLISIONES
        // Lo que usaba Keyboard::isKeyPressed() para moverse fluido
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            spriteJugador.move(100 * dt.asSeconds(), 0);
        }
    }

    void render(sf::RenderWindow& window) override {
        // AQUÍ VA TODO LO QUE ESTABA ENTRE WINDOW.CLEAR() Y WINDOW.DISPLAY()
        window.draw(spriteJugador);
    }

    // --- AQUÍ VAN LAS FUNCIONES DE LA CLASE ---
};