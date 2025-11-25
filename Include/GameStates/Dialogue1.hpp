#pragma once
#include "Core/GameState.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils/Enums.hpp"

// COPIAR Y PEGAR ESTA PLANTILLA DE ESCENA PARA CREAR UNA NUEVA

class Dialogue1 : public GameState {

private:
    // --- AQUÍ VAN LAS VARIABLES DE LA ESCENA ---
    
    sf::Texture texturaDialogo; // ¡IMPORTANTE! Las texturas deben ser miembros de la clase
    sf::Sprite spriteJugador;

    DialogueType m_type;
    std::string m_speakerName;
    std::string m_dialogueText;
    bool m_advanceClicked;
    
    // Si ya tienes clases, pones las instancias aquí:
    // Player jugador;
    // Map mapa;

public:
    
    // --- AQUÍ VAN LAS FUNCIONES DE LA CLASE ---

    void init() override;

    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;

    void update(sf::Time dt) override;

    void render(sf::RenderWindow& window) override;
};