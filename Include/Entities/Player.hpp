#pragma once

#include "Animator.hpp" // ¡Usamos nuestro animador!

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
    Player() 
        : m_animator(m_sprite, PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT), // Pasa el sprite al animador
          m_speed(PLAYER_SPEED), m_isMoving(false), m_lastDirection(ROW_P_IDLE_DOWN) {
        
        // Carga la textura (¡podrías pasar el path como argumento!)
        if (!m_texture.loadFromFile("player_spritesheet.png")) {
            std::cerr << "Error: No se pudo cargar player_spritesheet.png" << std::endl;
        }
        
        m_sprite.setTexture(m_texture);
        
        // Configura el origen del sprite
        m_sprite.setOrigin(PLAYER_FRAME_WIDTH / 2.f, PLAYER_FRAME_HEIGHT);

        // Configura todas las animaciones
        setupAnimations();
        
        // Reproduce la animación por defecto
        m_animator.play("idle_down");
    }

    // Configura la posición inicial
    void setPosition(float x, float y) {
        m_position.x = x; m_position.y = y;
        m_targetPosition = m_position;
        m_sprite.setPosition(m_position);
    }

    // Ordena al jugador que se mueva a un punto
    void moveTo(sf::Vector2f target) {
        m_targetPosition = target;
        m_isMoving = true;
    }

    // La función de actualización principal
    void update(sf::Time dt, const sf::Image& collisionImage) {
        if (m_isMoving) {
            sf::Vector2f direction = m_targetPosition - m_position;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            float movementStep = m_speed * dt.asSeconds();

            if (distance < movementStep || distance < 5.0f) {
                m_isMoving = false;
                m_position = m_targetPosition;
                playIdleAnimation(); // Llegamos, pon la animación de 'parado'
            } else {
                sf::Vector2f normDir = direction / distance;
                sf::Vector2f nextPos = m_position + normDir * movementStep;
                int nextX = static_cast<int>(nextPos.x);
                int nextY = static_cast<int>(nextPos.y);

                if (nextX >= 0 && nextX < (int)collisionImage.getSize().x &&
                    nextY >= 0 && nextY < (int)collisionImage.getSize().y &&
                    collisionImage.getPixel(nextX, nextY) == sf::Color::White) {
                    
                    m_position = nextPos; // Mueve al jugador
                    playWalkAnimation(normDir); // Reproduce la anim. de caminar
                
                } else {
                    m_isMoving = false; // Chocamos, detente
                    playIdleAnimation();
                }
            }
        } else {
            playIdleAnimation(); // Asegúrate de estar en 'idle' si no te mueves
        }

        // Actualiza el sprite a la posición física
        m_sprite.setPosition(m_position);
        // ¡Y actualiza la animación!
        m_animator.update(dt);
    }

    // Devuelve el sprite para dibujarlo o para el Y-Sorting
    sf::Sprite& getSprite() {
        return m_sprite;
    }

private:
    void setupAnimations() {
        // (nombre, fila, num_frames, duración_frame)
        m_animator.addAnimation("walk_up",    ROW_P_WALK_UP,    WALK_FRAMES, 0.1f);
        m_animator.addAnimation("walk_left",  ROW_P_WALK_LEFT,  WALK_FRAMES, 0.1f);
        m_animator.addAnimation("walk_down",  ROW_P_WALK_DOWN,  WALK_FRAMES, 0.1f);
        m_animator.addAnimation("walk_right", ROW_P_WALK_RIGHT, WALK_FRAMES, 0.1f);

        // Usamos la animación "thrust" como idle. Dura 1 solo frame.
        m_animator.addAnimation("idle_up",    ROW_P_IDLE_UP,    IDLE_FRAMES, 1.0f);
        m_animator.addAnimation("idle_left",  ROW_P_IDLE_LEFT,  IDLE_FRAMES, 1.0f);
        m_animator.addAnimation("idle_down",  ROW_P_IDLE_DOWN,  IDLE_FRAMES, 1.0f);
        m_animator.addAnimation("idle_right", ROW_P_IDLE_RIGHT, IDLE_FRAMES, 1.0f);
    }

    void playWalkAnimation(sf::Vector2f direction) {
        if (std::abs(direction.x) > std::abs(direction.y)) {
            if (direction.x > 0) {
                m_animator.play("walk_right");
                m_lastDirection = ROW_P_IDLE_RIGHT;
            } else {
                m_animator.play("walk_left");
                m_lastDirection = ROW_P_IDLE_LEFT;
            }
        } else {
            if (direction.y > 0) {
                m_animator.play("walk_down");
                m_lastDirection = ROW_P_IDLE_DOWN;
            } else {
                m_animator.play("walk_up");
                m_lastDirection = ROW_P_IDLE_UP;
            }
        }
    }

    void playIdleAnimation() {
        if (m_lastDirection == ROW_P_IDLE_UP) m_animator.play("idle_up");
        if (m_lastDirection == ROW_P_IDLE_LEFT) m_animator.play("idle_left");
        if (m_lastDirection == ROW_P_IDLE_DOWN) m_animator.play("idle_down");
        if (m_lastDirection == ROW_P_IDLE_RIGHT) m_animator.play("idle_right");
    }

    sf::Sprite m_sprite;
    sf::Texture m_texture;
    Animator m_animator; // ¡El jugador TIENE UN animador!

    sf::Vector2f m_position;
    sf::Vector2f m_targetPosition;
    float m_speed;
    bool m_isMoving;
    int m_lastDirection; // Para saber qué 'idle' poner
};