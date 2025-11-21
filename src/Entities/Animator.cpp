#include "Entities/Animator.hpp"

// Constructor
Animator::Animator(sf::Sprite& sprite, int frameWidth, int frameHeight)
    : m_sprite(&sprite), m_frameWidth(frameWidth), m_frameHeight(frameHeight), 
      m_timer(0.f), m_currentFrame(0) {
    // El cuerpo está vacío, todo se hace en la lista de inicialización
}

// Añade una nueva animación a su "repertorio"
void Animator::addAnimation(const std::string& name, int row, int frameCount, float duration, bool loop) {
    m_animations[name] = Animation(row, frameCount, duration, loop);
}

// La función principal: ¡reproduce una animación por su nombre!
void Animator::play(const std::string& name) {
    // Solo reinicia la animación si es una *nueva* animación
    if (m_currentAnimationName != name) {
        m_currentAnimationName = name;
        m_currentAnimation = &m_animations[name]; // Apunta a la animación activa
        m_timer = 0.f;
        m_currentFrame = 0;
        updateTextureRect(); // Pone el primer frame
    }
}

// Debe llamarse en CADA fotograma del juego
void Animator::update(sf::Time dt) {
    if (m_currentAnimation == nullptr) return; // No hay animación para reproducir

    m_timer += dt.asSeconds();

    // Si ha pasado el tiempo de un frame
    if (m_timer >= m_currentAnimation->duration) {
        m_timer -= m_currentAnimation->duration;
        m_currentFrame++;

        // Comprueba si la animación terminó
        if (m_currentFrame >= m_currentAnimation->frameCount) {
            if (m_currentAnimation->loop) {
                m_currentFrame = 0; // Vuelve al inicio si es un bucle
            } else {
                m_currentFrame = m_currentAnimation->frameCount - 1; // Se queda en el último frame
            }
        }
        updateTextureRect();
    }
}

// Función interna para actualizar el sprite
void Animator::updateTextureRect() {
    int left = m_currentFrame * m_frameWidth;
    int top = m_currentAnimation->row * m_frameHeight;
    m_sprite->setTextureRect(sf::IntRect(left, top, m_frameWidth, m_frameHeight));
}