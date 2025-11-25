#pragma once

#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>
#include "Animator.hpp"
#include "Utils/Geometry.hpp" 
#include "Utils/NavGrid.hpp"  

// Definimos constantes aquí para que sean fáciles de encontrar
const int PLAYER_FRAME_WIDTH = 64;
const int PLAYER_FRAME_HEIGHT = 64;
const float PLAYER_SPEED = 150.f;

// Filas del Spritesheet
const int ROW_P_WALK_UP = 8, ROW_P_WALK_LEFT = 9, ROW_P_WALK_DOWN = 10, ROW_P_WALK_RIGHT = 11;
const int ROW_P_IDLE_UP = 4, ROW_P_IDLE_LEFT = 5, ROW_P_IDLE_DOWN = 6, ROW_P_IDLE_RIGHT = 7;
const int WALK_FRAMES = 9;
const int IDLE_FRAMES = 1;

class Player {
public:
    Player();
    
    // La función de actualización principal
    void update(sf::Time dt);

    void render(sf::RenderWindow window);

    // Configura la posición inicial y cancela cualquier ruta
    void setPosition(float x, float y);


    // Asigna una nueva ruta al jugador
    void setPath(const std::vector<Point>& gridPath, const NavGrid& grid);

    // Devuelve el sprite para dibujarlo o para el Y-Sorting
    sf::Sprite& getSprite();
    
    // Devuelve la posición para el pathfinder
    Vec2f getPosition() const;

    // Devuelve true si el jugador está siguiendo una ruta
    bool isMoving() const;

    // Atributos de Diálogo del Jugador:
    std::string id;                // ID único del Jugador (ej: "Guardia_123").
    std::string dialogueKey;       // CLAVE: Qué diálogo ofrecer.
    
    // Para evitar el spam de diálogos:
    bool m_hasActiveDialogue = false; // TRUE si ya tiene una pila de diálogo abierta.

private:

    void setupAnimations();
    void playWalkAnimation(Vec2f direction);
    void playIdleAnimation();

    sf::Sprite m_sprite;
    sf::Texture m_texture;
    Animator m_animator;
    std::string m_currentAnimation;

    Vec2f m_position; // Posición actual precisa
    float m_speed;
    int m_lastDirection; // Para saber qué 'idle' poner

    std::vector<Vec2f> m_worldPath;    // La ruta convertida a coordenadas del mundo
    size_t m_currentIndex;           // El índice del punto al que nos dirigimos
    bool m_isMoving;                 // True si estamos siguiendo una ruta
};