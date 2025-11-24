#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

// Representa una animación concreta dentro del spritesheet
struct Animation {
    int row;
    int frameCount;
    float duration;
    int startColumn; // Columna inicial en el spritesheet
    bool loop;

    // Constructor (Declaración)
    Animation(int _row = 0, int _frameCount = 1, float _duration = 0.1f, bool _loop = true, int _startColumn = 0);
};

class Animator {
public:
    // Default Constructor
    Animator() : m_sprite(nullptr), m_currentAnimation(nullptr), m_frameWidth(0), m_frameHeight(0), m_timer(0.f), m_currentFrame(0) {}

    // Constructor
    Animator(sf::Sprite& sprite, int frameWidth, int frameHeight);

    /* Añade una animación al conjunto */
    void addAnimation(const std::string& name, int _row, int _frameCount, float _time, bool _loop = true, int _startColumn = 0);

    /* Reproduce la animación `name` */
    void play(const std::string& name);

    /* Avanza la animación en función del tiempo transcurrido */
    void update(sf::Time dt);

private:
    // Helper interno
    void updateTextureRect();

    sf::Sprite* m_sprite;
    std::map<std::string, Animation> m_animations;
    Animation* m_currentAnimation;
    std::string m_currentAnimationName;

    int m_frameWidth;
    int m_frameHeight;
    float m_timer;
    int m_currentFrame;
};