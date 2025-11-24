#include "Entities/NPC.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

NPC::NPC() : m_walkable(false) {
    m_speed = 60.0f; // Velocidad de movimiento en píxeles por segundo
    m_isMoving = false;
    m_currentIndex = 0;
    m_state = NPCState::Idle;
    m_stateTimer = 0.0f;
    m_lastDirection = ROW_NPC_IDLE_DOWN; // Dirección inicial mirando hacia abajo
    m_currentAnimation = "";

    setupAnimations();
}

void NPC::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

void NPC::setTexture(const std::string& texturePath) {
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Error al cargar la textura: " << texturePath << std::endl;
        return; // Salimos de la función si hay un error
    }
    m_sprite.setTexture(m_texture);
}

void NPC::setWalkable(bool isWalkable) {
    m_walkable = isWalkable;
}

void NPC::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void NPC::update(sf::Time dt, const NavGrid& grid) {
    updateAI(dt, grid);

    if (m_isMoving) {
        Vec2f target = m_worldPath[m_currentIndex];
        Vec2f direction = target - m_position;
        float distance = direction.magnitude();
        float movementStep = m_speed * dt.asSeconds();

        if (distance < movementStep || distance < 2.0f) {
            m_position = target;
            m_currentIndex++;

            if (m_currentIndex >= m_worldPath.size()) {
                m_isMoving = false;
                m_worldPath.clear();
                m_currentIndex = 0;
                startIdle(); // Al llegar, pasamos a Idle
            } else {
                Vec2f nextTarget = m_worldPath[m_currentIndex];
                Vec2f nextDir = nextTarget - m_position;
                if (nextDir.magnitude() > 0.001f) {
                    playWalkAnimation(nextDir.normalized());
                }
            }
        } else {
            Vec2f normDir = direction.normalized();
            m_position = m_position + (normDir * movementStep);
            playWalkAnimation(normDir);
        }
    } else {
        // Si no se mueve, nos aseguramos de que esté en idle (o action)
        if (m_state == NPCState::Idle) {
             playIdleAnimation();
        }
    }

    m_sprite.setPosition(m_position.x, m_position.y);
    m_animator.update(dt);
}

void NPC::updateAI(sf::Time dt, const NavGrid& grid) {
    // Máquina de estados simple
    if (m_state == NPCState::Idle) {
        m_stateTimer -= dt.asSeconds();
        if (m_stateTimer <= 0) {
            // Decide patrullar o seguir en Idle (o Action)
            int choice = rand() % 10;
            if (m_walkable && choice < 6) { // 60% probabilidad de patrullar SI es caminable
                pickRandomPatrolPoint(grid);
            } else {
                // Reiniciar idle con otra animación o tiempo
                startIdle();
            }
        }
    } /*else if (m_state == NPCState::Patrol) {
        // Si estamos patrullando, el movimiento se maneja en update()
        // Si terminamos de movernos (m_isMoving false), pasamos a Idle en update()
    } else if (m_state == NPCState::Action) {
        m_stateTimer -= dt.asSeconds();
        if (m_stateTimer <= 0) {
            startIdle();
        }
    }*/
}

void NPC::pickRandomPatrolPoint(const NavGrid& grid) {
    // Intentar encontrar un punto caminable aleatorio
    int attempts = 0;
    while (attempts < 10) {
        int rX = rand() % grid.getWidth();
        int rY = rand() % grid.getHeight();
        Point targetGrid(rX, rY);

        if (grid.isWalkable(targetGrid)) {
            
            Point currentGrid = grid.worldToGrid(m_position);
            int dx = (rand() % 11) - 5;
            int dy = (rand() % 11) - 5;
            Point nextGrid(currentGrid.x + dx, currentGrid.y + dy);
            
            if (nextGrid.x >= 0 && nextGrid.x < grid.getWidth() &&
                nextGrid.y >= 0 && nextGrid.y < grid.getHeight() &&
                grid.isWalkable(nextGrid)) {
                
                m_worldPath.clear();
                m_worldPath.push_back(grid.gridToWorldCenter(nextGrid));
                m_isMoving = true;
                m_currentIndex = 0;
                m_state = NPCState::Patrol;
                return;
            }
        }
        attempts++;
    }
   
    startIdle();
}

void NPC::startIdle() {
    m_state = NPCState::Idle;
    m_stateTimer = 2.0f + static_cast<float>(rand() % 300) / 100.0f; // 2 a 5 segundos
    playIdleAnimation();

    /*// Ocasionalmente reproducir una animación especial
    int animRandom = rand() % 100;
    if (animRandom < 20) { 
        m_state = NPCState::Action;
        m_animator.play("Pose_Espalda");
        m_stateTimer = 2.0f; 
    } 
    else if (animRandom >= 20 && animRandom < 40) {
        m_animator.play("Pose_Pecho");
        m_stateTimer = 2.0f; 
    }
    else if (animRandom >= 40 && animRandom < 45) {
        m_animator.play("Pose_Descanso");
        m_stateTimer = 5.0f; 
    }
    else {
        playIdleAnimation();
    }*/
}

sf::Sprite& NPC::getSprite() {
    return m_sprite;
}

sf::Texture& NPC::getTexture() {
    return m_texture;
}

Vec2f NPC::getPosition() const {
    return m_position;
}

void NPC::setupAnimations() {
    // Caminar
    m_animator.addAnimation("walk_up",    ROW_NPC_WALK_UP,    9, 0.1f);
    m_animator.addAnimation("walk_left",  ROW_NPC_WALK_LEFT,  9, 0.1f);
    m_animator.addAnimation("walk_down",  ROW_NPC_WALK_DOWN,  9, 0.1f);
    m_animator.addAnimation("walk_right", ROW_NPC_WALK_RIGHT, 9, 0.1f);

    // Idle
    m_animator.addAnimation("idle_up",    ROW_NPC_IDLE_UP,    1, 1.0f);
    m_animator.addAnimation("idle_left",  ROW_NPC_IDLE_LEFT,  1, 1.0f);
    m_animator.addAnimation("idle_down",  ROW_NPC_IDLE_DOWN,  1, 1.0f);
    m_animator.addAnimation("idle_right", ROW_NPC_IDLE_RIGHT, 1, 1.0f);
    
    // Acciones especiales (ejemplo)
    /*
    m_animator.addAnimation("Pose_Espalda", 0 , 1 , 1.0f, false, 5);
    m_animator.addAnimation("Pose_Pecho", 2 , 1 , 1.0f, false, 1);
    m_animator.addAnimation("Pose_Descanso", 20 , 6 , 0.5f, false, 0);*/
}

void NPC::playWalkAnimation(Vec2f normDir) {
    std::string newAnimation = "";
    if (std::abs(normDir.x) > std::abs(normDir.y)) {
        if (normDir.x > 0) {
            newAnimation = "walk_right";
            m_lastDirection = ROW_NPC_IDLE_RIGHT;
        } else {
            newAnimation = "walk_left";
            m_lastDirection = ROW_NPC_IDLE_LEFT;
        }
    } else {
        if (normDir.y > 0) {
            newAnimation = "walk_down";
            m_lastDirection = ROW_NPC_IDLE_DOWN;
        } else {
            newAnimation = "walk_up";
            m_lastDirection = ROW_NPC_IDLE_UP;
        }
    }

    if (m_currentAnimation != newAnimation) {
        m_animator.play(newAnimation);
        m_currentAnimation = newAnimation;
    }
}

void NPC::playIdleAnimation() {
    std::string newAnimation = "";
    if (m_lastDirection == ROW_NPC_IDLE_UP) newAnimation = "idle_up";
    else if (m_lastDirection == ROW_NPC_IDLE_LEFT) newAnimation = "idle_left";
    else if (m_lastDirection == ROW_NPC_IDLE_DOWN) newAnimation = "idle_down";
    else if (m_lastDirection == ROW_NPC_IDLE_RIGHT) newAnimation = "idle_right";

    if (newAnimation.empty()) newAnimation = "idle_down";

    if (m_currentAnimation != newAnimation) {
        m_animator.play(newAnimation);
        m_currentAnimation = newAnimation;
    }
}
