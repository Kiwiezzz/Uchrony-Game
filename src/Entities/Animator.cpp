#include "Entities/Animator.hpp"

// --- Implementación de Animation ---

Animation::Animation(int r, int fc, float d, bool l, int sc)
    : row(r), frameCount(fc), duration(d), loop(l), startColumn(sc) {
}


// --- Implementación de Animator ---

Animator::Animator(sf::Sprite& sprite, int frameWidth, int frameHeight)
    : m_sprite(&sprite), 
      m_frameWidth(frameWidth), 
      m_frameHeight(frameHeight),
      m_timer(0.f), 
      m_currentFrame(0), 
      m_currentAnimation(nullptr) // Importante inicializar el puntero a null
{
}

void Animator::addAnimation(const std::string& name, int row, int frameCount, float duration, bool loop, int startColumn) {
    // Insertamos la animación en el mapa
    m_animations[name] = Animation(row, frameCount, duration, loop, startColumn);
}

void Animator::play(const std::string& name) {
    // Si ya se está reproduciendo esa animación, no hacemos nada
    if (m_currentAnimationName != name) {
        m_currentAnimationName = name;
        // Buscamos la animación en el mapa y guardamos el puntero
        m_currentAnimation = &m_animations[name];
        
        // Reseteamos estado
        m_timer = 0.f;
        m_currentFrame = 0;
        
        updateTextureRect();
    }
}

void Animator::update(sf::Time dt) {
    // Si no hay animación seleccionada, salimos
    if (m_currentAnimation == nullptr) return;

    m_timer += dt.asSeconds();

    if (m_timer >= m_currentAnimation->duration) {
        // Restamos la duración para mantener precisión (en vez de poner a 0)
        m_timer -= m_currentAnimation->duration;
        m_currentFrame++;

        // Comportamiento al alcanzar el final
        if (m_currentFrame >= m_currentAnimation->frameCount) {
            if (m_currentAnimation->loop) {
                m_currentFrame = 0;
            } else {
                // Si no es loop, se queda en el último frame
                m_currentFrame = m_currentAnimation->frameCount - 1;
            }
        }
        updateTextureRect();
    }
}

void Animator::updateTextureRect() {
    if (m_currentAnimation == nullptr) return;

    // Usamos startColumn para desplazar el inicio de la animación
    int left = (m_currentFrame + m_currentAnimation->startColumn) * m_frameWidth;
    int top = m_currentAnimation->row * m_frameHeight;
    
    m_sprite->setTextureRect(sf::IntRect(left, top, m_frameWidth, m_frameHeight));
}

void Animator::setSprite(sf::Sprite& sprite) {
    m_sprite = &sprite;
    // Actualizar el texture rect si hay una animación activa
    if (m_currentAnimation != nullptr) {
        updateTextureRect();
    }
}