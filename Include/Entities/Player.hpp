#pragma once

#include "Animator.hpp" // ¡Usamos nuestro animador!

#include <iostream>
#include <algorithm>
#include <cmath>

// Definimos constantes aquí para que sean fáciles de encontrar
const int PLAYER_FRAME_WIDTH = 64;
const int PLAYER_FRAME_HEIGHT = 64;
const float PLAYER_SPEED = 150.f;

// Filas del Spritesheet (igual que antes)
const int ROW_P_WALK_UP = 8, ROW_P_WALK_LEFT = 9, ROW_P_WALK_DOWN = 10, ROW_P_WALK_RIGHT = 11;
const int ROW_P_IDLE_UP = 4, ROW_P_IDLE_LEFT = 5, ROW_P_IDLE_DOWN = 6, ROW_P_IDLE_RIGHT = 7;
const int WALK_FRAMES = 9; // LPC walkcycle tiene 9 frames
const int IDLE_FRAMES = 1; // La animación "thrust" la usaremos como 1 solo frame

class Player {
public:
    // El constructor ahora inicializa el animador
    Player();

    // Configura la posición inicial
    void setPosition(float x, float y);

    // Ordena al jugador que se mueva a un punto
    void moveTo(sf::Vector2f target);

    // La función de actualización principal
    void update(sf::Time dt, const sf::Image& collisionImage);

    // Devuelve el sprite para dibujarlo o para el Y-Sorting
    sf::Sprite& getSprite();

private:
    void setupAnimations();

    void playWalkAnimation(sf::Vector2f direction);

    void playIdleAnimation();

    sf::Sprite m_sprite;
    sf::Texture m_texture;
    Animator m_animator; // ¡El jugador TIENE UN animador!

    sf::Vector2f m_position;
    sf::Vector2f m_targetPosition;
    float m_speed;
    bool m_isMoving;
    int m_lastDirection; // Para saber qué 'idle' poner
};