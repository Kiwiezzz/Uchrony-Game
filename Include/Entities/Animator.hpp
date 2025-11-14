#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <iostream>

// Representa una animación concreta dentro del spritesheet

struct Animation {
    // Fila en el spritesheet donde están los frames de la animación
    int row;
    // Número de frames que tiene la animación (columnas contiguas)
    int frameCount;
    // Duración de CADA frame en segundos
    float duration;
    // Si la animación debe repetirse cuando alcanza el final
    bool loop;

    Animation(int r = 0, int fc = 1, float d = 0.1f, bool l = true)
        : row(r), frameCount(fc), duration(d), loop(l) {}
};

class Animator {
public:

    Animator(sf::Sprite& sprite, int frameWidth, int frameHeight)
        : m_sprite(&sprite), m_frameWidth(frameWidth), m_frameHeight(frameHeight),
          m_timer(0.f), m_currentFrame(0) {
    }

    /* Añade una animación al conjunto conocido por este Animator.
     * name: identificador único (ej. "walk_down")
     * row: fila del spritesheet
     * frameCount: número de frames (columnas)
     * duration: duración de cada frame en segundos
     * loop: si la animación debe volver al inicio
     */
    void addAnimation(const std::string& name, int row, int frameCount, float duration, bool loop = true) {
        m_animations[name] = Animation(row, frameCount, duration, loop);
    }

    /* Reproduce la animación `name`. Si ya se estaba reproduciendo esa misma
     * animación no hace nada; si es distinta, resetea temporizador y frame.
     */
    void play(const std::string& name) {
        if (m_currentAnimationName != name) {
            m_currentAnimationName = name;
            m_currentAnimation = &m_animations[name];
            m_timer = 0.f;
            m_currentFrame = 0;
            updateTextureRect();
        }
    }

    /* Avanza la animación en función del tiempo transcurrido `dt`.
     * Debe llamarse desde el bucle principal del juego.
     */
    void update(sf::Time dt) {
        if (m_currentAnimation == nullptr) return; // nada que reproducir

        m_timer += dt.asSeconds();

        if (m_timer >= m_currentAnimation->duration) {
            m_timer -= m_currentAnimation->duration;
            m_currentFrame++;

            // Comportamiento al alcanzar el final de la animación
            if (m_currentFrame >= m_currentAnimation->frameCount) {
                if (m_currentAnimation->loop) {
                    m_currentFrame = 0;
                } else {
                    m_currentFrame = m_currentAnimation->frameCount - 1;
                }
            }
            updateTextureRect();
        }
    }

private:
    // Actualiza el `IntRect` del sprite en base al frame actual y la fila
    void updateTextureRect() {
        int left = m_currentFrame * m_frameWidth;
        int top = m_currentAnimation->row * m_frameHeight;
        m_sprite->setTextureRect(sf::IntRect(left, top, m_frameWidth, m_frameHeight));
    }

    // Sprite animado
    sf::Sprite* m_sprite;
    // Mapa de animaciones disponibles por nombre
    std::map<std::string, Animation> m_animations;
    // Puntero a la animación activa (apunta a un valor dentro de m_animations)
    Animation* m_currentAnimation = nullptr;
    // Nombre de la animación activa (útil para evitar reinicios innecesarios)
    std::string m_currentAnimationName;

    int m_frameWidth;
    int m_frameHeight;
    float m_timer;       // temporizador acumulado para avanzar frames
    int m_currentFrame;  // índice del frame actual (0..frameCount-1)
};