#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

// Una estructura simple para definir una animación
struct Animation {
    int row;           // Fila en el spritesheet
    int frameCount;    // Cuántos frames tiene
    float duration;    // Duración de CADA frame
    bool loop;         // ¿Debe repetirse?

    Animation(int r = 0, int fc = 1, float d = 0.1f, bool l = true)
        : row(r), frameCount(fc), duration(d), loop(l) {}
};

class Animator {
public:
    // Constructor: necesita el sprite que va a animar y el tamaño de los frames
    Animator(sf::Sprite& sprite, int frameWidth, int frameHeight)
        : m_sprite(&sprite), m_frameWidth(frameWidth), m_frameHeight(frameHeight), 
          m_timer(0.f), m_currentFrame(0) {
    }

    // Añade una nueva animación a su "repertorio"
    void addAnimation(const std::string& name, int row, int frameCount, float duration, bool loop = true) {
        m_animations[name] = Animation(row, frameCount, duration, loop);
    }

    // La función principal: ¡reproduce una animación por su nombre!
    void play(const std::string& name) {
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
    void update(sf::Time dt) {
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

private:
    // Función interna para actualizar el sprite
    void updateTextureRect() {
        int left = m_currentFrame * m_frameWidth;
        int top = m_currentAnimation->row * m_frameHeight;
        m_sprite->setTextureRect(sf::IntRect(left, top, m_frameWidth, m_frameHeight));
    }

    sf::Sprite* m_sprite;                    // Puntero al sprite que animamos
    std::map<std::string, Animation> m_animations; // Todas las animaciones
    Animation* m_currentAnimation = nullptr; // Puntero a la animación actual
    std::string m_currentAnimationName;

    int m_frameWidth;
    int m_frameHeight;
    float m_timer;
    int m_currentFrame;
};