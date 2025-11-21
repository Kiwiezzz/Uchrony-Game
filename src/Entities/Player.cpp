#include "Entities/Player.hpp"

Player::Player() 
    : m_animator(m_sprite, PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT), 
        m_speed(PLAYER_SPEED), m_isMoving(false), m_lastDirection(ROW_P_IDLE_DOWN) {
    
    // Carga la textura (¡podrías pasar el path como argumento!)
    if (!m_texture.loadFromFile("assets/textures/player_spritesheet.png")) { // <-- ARREGLADO
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
void Player::setPosition(float x, float y) {
    m_position.x = x; m_position.y = y;
    m_targetPosition = m_position;
    m_sprite.setPosition(m_position);
}

// Ordena al jugador que se mueva a un punto
void Player::moveTo(sf::Vector2f target) {
    m_targetPosition = target;
    m_isMoving = true;
}

// La función de actualización principal
void Player::update(sf::Time dt, const sf::Image& collisionImage) {
    if (m_isMoving) {
        sf::Vector2f direction = m_targetPosition - m_position;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        float movementStep = m_speed * dt.asSeconds();

        if (distance < movementStep || distance < 5.0f) {
            m_isMoving = false;
            m_position = m_targetPosition;
            playIdleAnimation(); // Llegamos, pon la animación de 'parado'
        } 
        else 
        {
            sf::Vector2f normDir = direction / distance;
            sf::Vector2f nextPos = m_position + normDir * movementStep;

            // 1. Define el ancho de tu colisión.
            // Tu sprite tiene 64px de ancho, escalado x2 = 128px.
            // El origen está en el centro (32*2 = 64px).
            // Usemos un 80% de ese ancho para no atascarnos.
            float collisionHalfWidth = (PLAYER_FRAME_WIDTH / 2.f) * m_sprite.getScale().x * 0.8f;

            // 2. Define los 3 puntos de colisión
            int cX = static_cast<int>(nextPos.x); // Centro (pies)
            int cY = static_cast<int>(nextPos.y); // Centro (pies)
            int lX = static_cast<int>(nextPos.x - collisionHalfWidth); // Izquierda
            int rX = static_cast<int>(nextPos.x + collisionHalfWidth); // Derecha

            // 3. Comprueba que los 3 puntos estén dentro de los límites
            bool centerInBounds = cX >= 0 && cX < (int)collisionImage.getSize().x && cY >= 0 && cY < (int)collisionImage.getSize().y;
            bool leftInBounds   = lX >= 0 && lX < (int)collisionImage.getSize().x && cY >= 0 && cY < (int)collisionImage.getSize().y;
            bool rightInBounds  = rX >= 0 && rX < (int)collisionImage.getSize().x && cY >= 0 && cY < (int)collisionImage.getSize().y;

            // 4. Comprueba el color si están dentro de los límites
            if (centerInBounds && leftInBounds && rightInBounds &&
                collisionImage.getPixel(cX, cY) == sf::Color::White &&
                collisionImage.getPixel(lX, cY) == sf::Color::White &&
                collisionImage.getPixel(rX, cY) == sf::Color::White)
            {
                // 5. ¡CAMINO LIBRE! Mueve al jugador
                m_position = nextPos;
                playWalkAnimation(normDir);
            }
            else
            {
                // 6. ¡COLISIÓN! Detén el movimiento
                m_isMoving = false;
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
sf::Sprite& Player::getSprite() {
    return m_sprite;
}


void Player::setupAnimations() {
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

void Player::playWalkAnimation(sf::Vector2f direction) {
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

void Player::playIdleAnimation() {
    if (m_lastDirection == ROW_P_IDLE_UP) m_animator.play("idle_up");
    if (m_lastDirection == ROW_P_IDLE_LEFT) m_animator.play("idle_left");
    if (m_lastDirection == ROW_P_IDLE_DOWN) m_animator.play("idle_down");
    if (m_lastDirection == ROW_P_IDLE_RIGHT) m_animator.play("idle_right");
}