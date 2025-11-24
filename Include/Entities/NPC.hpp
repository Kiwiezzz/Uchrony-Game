#pragma once

#include <SFML/Graphics.hpp>
#include "Animator.hpp"
#include "Utils/Geometry.hpp"
#include "Utils/NavGrid.hpp"
#include <vector>
#include <string>

// Constantes para el NPC (ajustar según el spritesheet)
const int NPC_FRAME_WIDTH = 64;
const int NPC_FRAME_HEIGHT = 64;
const float NPC_SPEED = 100.f;

// Filas del Spritesheet (Asumiendo estructura similar al Player)
// Ajustar estos valores si el spritesheet es diferente
const int ROW_NPC_WALK_UP = 8, ROW_NPC_WALK_LEFT = 9, ROW_NPC_WALK_DOWN = 10, ROW_NPC_WALK_RIGHT = 11;
const int ROW_NPC_IDLE_UP = 4, ROW_NPC_IDLE_LEFT = 5, ROW_NPC_IDLE_DOWN = 6, ROW_NPC_IDLE_RIGHT = 7;

// Animaciones extra para Idle (ejemplo)
const int ROW_NPC_ACTION_1 = 0; 
const int ROW_NPC_ACTION_2 = 1;

enum class NPCState {
    Idle,
    Patrol,
    Action // Estado para animaciones especiales
};

class NPC {
public:
    NPC() = default;

    void init(std::string path, Vec2f position, bool walkable);
    void update(sf::Time dt, const NavGrid& grid);
    void render(sf::Window& window);

    void setPosition(float x, float y);
    sf::Sprite& getSprite();
    Vec2f getPosition() const;

private:
    void setupAnimations();
    void playWalkAnimation(Vec2f direction);
    void playIdleAnimation();
    
    // IA
    void updateAI(sf::Time dt, const NavGrid& grid);
    void pickRandomPatrolPoint(const NavGrid& grid);
    void startIdle();

    sf::Sprite m_sprite;
    sf::Texture m_texture;
    Animator m_animator;
    bool m_walkable;
    std::string m_currentAnimation;

    Vec2f m_position;
    float m_speed;
    int m_lastDirection;

    // Pathfinding
    std::vector<Vec2f> m_worldPath;
    size_t m_currentIndex;
    bool m_isMoving;

    // State Machine
    NPCState m_state;
    float m_stateTimer; // Temporizador para cambiar de estado
};
