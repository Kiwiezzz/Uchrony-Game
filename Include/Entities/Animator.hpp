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
    Animator(sf::Sprite& sprite, int frameWidth, int frameHeight);

    // Añade una nueva animación a su "repertorio"
    void addAnimation(const std::string& name, int row, int frameCount, float duration, bool loop = true);

    // La función principal: ¡reproduce una animación por su nombre!
    void play(const std::string& name);

    // Debe llamarse en CADA fotograma del juego
    void update(sf::Time dt);

private:
    // Función interna para actualizar el sprite
    void updateTextureRect();

    sf::Sprite* m_sprite;                    // Puntero al sprite que animamos
    std::map<std::string, Animation> m_animations; // Todas las animaciones
    Animation* m_currentAnimation = nullptr; // Puntero a la animación actual
    std::string m_currentAnimationName;

    int m_frameWidth;
    int m_frameHeight;
    float m_timer;
    int m_currentFrame;
};