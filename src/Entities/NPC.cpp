#include "Entities/NPC.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

void NPC::init(std::string path, Vec2f position, bool walkable) {
    // Primero inicializamos variables básicas
    m_speed = NPC_SPEED;
    m_isMoving = false;
    m_walkable = walkable;
    m_lastDirection = ROW_NPC_IDLE_DOWN;
    m_currentIndex = 0;
    m_state = NPCState::Idle;
    m_stateTimer = 0.f;

    // Cargar la textura ANTES de inicializar el Animator
    if (!m_texture.loadFromFile(path)) {
        std::cerr << "Error: No se pudo cargar el sprite del NPC: " << path << std::endl;
    }

    // Asignar la textura al sprite
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(NPC_FRAME_WIDTH / 2.f, NPC_FRAME_HEIGHT);

    // Inicializar el Animator con las dimensiones de frame
    m_animator = Animator(m_sprite, NPC_FRAME_WIDTH, NPC_FRAME_HEIGHT);
    
    // IMPORTANTE: Actualizar explícitamente el puntero del sprite en el Animator
    // Esto es necesario porque el operador de asignación puede no copiar correctamente el puntero
    m_animator.setSprite(m_sprite);

    // Configurar y reproducir animaciones
    setupAnimations();
    m_animator.play("idle_down");
    m_currentAnimation = "idle_down";
    m_animator.update(sf::Time::Zero); // Aplicar frame inicial inmediatamente

    setPosition(position.x, position.y);
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

void NPC::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void NPC::setPosition(float x, float y) {
    m_position = Vec2f(x, y);
    m_sprite.setPosition(m_position.x, m_position.y);
    m_worldPath.clear();
    m_isMoving = false;
    m_currentIndex = 0;
    startIdle();
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
    } else if (m_state == NPCState::Patrol) {
        // Si estamos patrullando, el movimiento se maneja en update()
        // Si terminamos de movernos (m_isMoving false), pasamos a Idle en update()
    } else if (m_state == NPCState::Action) {
        m_stateTimer -= dt.asSeconds();
        if (m_stateTimer <= 0) {
            startIdle();
        }
    }
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
}

sf::Sprite& NPC::getSprite() {
    return m_sprite;
}

Vec2f NPC::getPosition() const {
    return m_position;
}

void NPC::updateAnimatorSprite() {
    // CRÍTICO: Después de copiar el NPC, el sprite de la copia 
    // todavía apunta a la textura del NPC original.
    // Necesitamos reconectar el sprite con SU PROPIA textura (la copiada)
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(NPC_FRAME_WIDTH / 2.f, NPC_FRAME_HEIGHT);
    
    // Luego reconectar el Animator con el sprite actualizado
    m_animator.setSprite(m_sprite);

    // Asegurar que el sprite tenga el frame correcto aplicado inmediatamente
    m_animator.update(sf::Time::Zero);
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

void NPC::addAnimation(const std::string& name, int _row, int _frameCount, float _time, bool _loop, int _startColumn) {
    m_animator.addAnimation(name, _row, _frameCount, _time, _loop, _startColumn);
}

void NPC::playAction(std::string name, float duration) {
    m_state = NPCState::Action;
    m_stateTimer = duration;
    m_animator.play(name);
    m_currentAnimation = name;
}

void NPC::stopMovement() {
    m_isMoving = false;
    m_worldPath.clear();
    m_currentIndex = 0;
    m_walkable = false; // Stop patrolling
    startIdle();
}

void NPC::setWalkable(bool walkable) {
    m_walkable = walkable;
}

void NPC::faceDirection(Vec2f direction) {
    Vec2f normDir = direction.normalized();
    if (std::abs(normDir.x) > std::abs(normDir.y)) {
        if (normDir.x > 0) m_lastDirection = ROW_NPC_IDLE_RIGHT;
        else m_lastDirection = ROW_NPC_IDLE_LEFT;
    } else {
        if (normDir.y > 0) m_lastDirection = ROW_NPC_IDLE_DOWN;
        else m_lastDirection = ROW_NPC_IDLE_UP;
    }
    playIdleAnimation();
}

NPCState NPC::getState() const {
    return m_state;
}