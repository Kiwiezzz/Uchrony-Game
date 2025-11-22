#include "Entities/Player.hpp"
#include "Utils/NavGrid.hpp"
#include <iostream>
#include <cmath>


Player::Player()
    : m_animator(m_sprite, PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT),
      m_speed(PLAYER_SPEED),
      m_isMoving(false),
      m_lastDirection(ROW_P_IDLE_DOWN),
      m_currentIndex(0)
{
    // Cargar textura del jugador
    if (!m_texture.loadFromFile("assets/textures/player_spritesheet.png")) {
        std::cerr << "Error: No se pudo cargar player_spritesheet.png" << std::endl;
    }

    m_sprite.setTexture(m_texture);
    // Origen del sprite para que la posición se refiera al pie del personaje
    m_sprite.setOrigin(PLAYER_FRAME_WIDTH / 2.f, PLAYER_FRAME_HEIGHT);

    // Registrar animaciones (walk/idle para 4 direcciones)
    setupAnimations();

    // Estado inicial: quieto mirando hacia abajo
    m_animator.play("idle_down");
    m_currentAnimation = "idle_down";
}

// setPosition
// - Pone la posición exacta del jugador y cancela cualquier ruta activa.
void Player::setPosition(float x, float y) {
    m_position = Vec2f(x, y);
    m_sprite.setPosition(m_position.x, m_position.y);

    // Cancelar cualquier seguimiento de ruta
    m_worldPath.clear();
    m_isMoving = false;
    m_currentIndex = 0;
    playIdleAnimation();
}

// Mueve al jugador siguiendo la ruta establecida por setPath.
// Actualiza la posición y la animación según el tiempo transcurrido `dt`.
void Player::update(sf::Time dt) {

    //Esta quieto el jugador?
    if (m_isMoving) {
        // Obtener objetivo actual y calcular vector dirección
        Vec2f target = m_worldPath[m_currentIndex];
        Vec2f direction = target - m_position;
        float distance = direction.magnitude();
        float movementStep = m_speed * dt.asSeconds();

        // Si el siguiente paso nos alcanza o estamos muy cerca, saltamos al nodo
        if (distance < movementStep || distance < 2.0f) {
            m_position = target;
            m_currentIndex++;

            // Si ya no quedan nodos, paramos y ponemos idle
            if (m_currentIndex >= m_worldPath.size()) {
                m_isMoving = false;
                m_worldPath.clear();
                m_currentIndex = 0;
                playIdleAnimation();
            }
            else 
            {
                // Si quedan nodos, iniciar animación de caminata hacia el siguiente
                Vec2f nextTarget = m_worldPath[m_currentIndex];
                Vec2f nextDir = nextTarget - m_position;
                if (nextDir.magnitude() > 0.001f) {
                    playWalkAnimation(nextDir.normalized());
                }
            }
        } else {
            // Movimiento suave hacia el siguiente nodo
            Vec2f normDir = direction.normalized();
            m_position = m_position + (normDir * movementStep);
            playWalkAnimation(normDir);
        }

    } else {
        // No hay ruta: reproducir animación idle según última dirección
        playIdleAnimation();
    }

    // Actualiza la posición del sprite y la animación
    m_sprite.setPosition(m_position.x, m_position.y);
    m_animator.update(dt);
}

// setPath
// - Convierte una ruta en coordenadas de grilla (Point) a coordenadas del
//   mundo (centro de celda) y activa el seguimiento si la ruta no está vacía.
void Player::setPath(const std::vector<Point>& gridPath, const NavGrid& grid) {
    m_worldPath.clear();
    m_currentIndex = 0;

    for (const Point& p : gridPath) {
        m_worldPath.push_back(grid.gridToWorldCenter(p));
    }

    m_isMoving = !m_worldPath.empty();
}


sf::Sprite& Player::getSprite() {
    return m_sprite;
}

Vec2f Player::getPosition() const {
    return m_position;
}

bool Player::isMoving() const {
    return m_isMoving;
}

void Player::setupAnimations() {
    // Registrar animaciones de caminata (4 direcciones)
    m_animator.addAnimation("walk_up",    ROW_P_WALK_UP,    WALK_FRAMES, 0.1f);
    m_animator.addAnimation("walk_left",  ROW_P_WALK_LEFT,  WALK_FRAMES, 0.1f);
    m_animator.addAnimation("walk_down",  ROW_P_WALK_DOWN,  WALK_FRAMES, 0.1f);
    m_animator.addAnimation("walk_right", ROW_P_WALK_RIGHT, WALK_FRAMES, 0.1f);

    // Registrar animaciones de idle (un único frame por dirección)
    m_animator.addAnimation("idle_up",    ROW_P_IDLE_UP,    IDLE_FRAMES, 1.0f);
    m_animator.addAnimation("idle_left",  ROW_P_IDLE_LEFT,  IDLE_FRAMES, 1.0f);
    m_animator.addAnimation("idle_down",  ROW_P_IDLE_DOWN,  IDLE_FRAMES, 1.0f);
    m_animator.addAnimation("idle_right", ROW_P_IDLE_RIGHT, IDLE_FRAMES, 1.0f);
}

void Player::playWalkAnimation(Vec2f normDir) {

    // Determina la animación de caminata adecuada en función de la
    // componente dominante del vector de dirección normalizado.
    std::string newAnimation = "";

    if (std::abs(normDir.x) > std::abs(normDir.y)) {
        // Movimiento horizontal dominante
        if (normDir.x > 0) {
            newAnimation = "walk_right";
            m_lastDirection = ROW_P_IDLE_RIGHT;
        } else {
            newAnimation = "walk_left";
            m_lastDirection = ROW_P_IDLE_LEFT;
        }
    } else {
        // Movimiento vertical dominante
        if (normDir.y > 0) {
            newAnimation = "walk_down";
            m_lastDirection = ROW_P_IDLE_DOWN;
        } else {
            newAnimation = "walk_up";
            m_lastDirection = ROW_P_IDLE_UP;
        }
    }

    // Solo cambiar la animación si es distinta a la actual
    if (m_currentAnimation != newAnimation) {
        m_animator.play(newAnimation);
        m_currentAnimation = newAnimation;
    }
}

void Player::playIdleAnimation() {
    
    // Selecciona la animación idle correspondiente según la dirección
    std::string newAnimation = "";

    if (m_lastDirection == ROW_P_IDLE_UP) newAnimation = "idle_up";
    else if (m_lastDirection == ROW_P_IDLE_LEFT) newAnimation = "idle_left";
    else if (m_lastDirection == ROW_P_IDLE_DOWN) newAnimation = "idle_down";
    else if (m_lastDirection == ROW_P_IDLE_RIGHT) newAnimation = "idle_right";

    if (newAnimation.empty()) newAnimation = "idle_down";

    if (m_currentAnimation != newAnimation) {
        m_animator.play(newAnimation);
        m_currentAnimation = newAnimation;
    }
}