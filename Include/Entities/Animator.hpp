#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

// Representa una animación concreta dentro del spritesheet
struct Animation {
    int row;
    int frameCount;
    float duration;
    bool loop;

    // Constructor (Declaración)
    Animation(int r = 0, int fc = 1, float d = 0.1f, bool l = true);
};

class Animator {
public:
    // Constructor
    Animator(sf::Sprite& sprite, int frameWidth, int frameHeight);

    /* Añade una animación al conjunto */
    void addAnimation(const std::string& name, int row, int frameCount, float duration, bool loop = true);

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