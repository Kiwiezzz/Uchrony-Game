#include "Utils/GameUtilities.hpp"
#include <iostream>
#include <cmath>

namespace GameUtils {

    sf::Vector2f getMouseWorldPosition(const sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }

    void markPosition(sf::RenderWindow& window, sf::Vector2f position, sf::Color color, float radius) {
        sf::CircleShape marker(radius);
        marker.setOrigin(radius, radius); // Centra el círculo
        marker.setPosition(position);
        marker.setFillColor(sf::Color::Transparent);
        marker.setOutlineColor(color);
        marker.setOutlineThickness(2.f);
        window.draw(marker);
    }

    void logPosition(sf::Vector2f position, const std::string& prefix) {
        std::cout << prefix << ": (x=" << position.x << ", y=" << position.y << ")" << std::endl;
    }

    void debugFollowMouse(sf::Sprite& sprite, sf::RenderWindow& window, const std::string& prefix) {
        sf::Vector2f mousePos = getMouseWorldPosition(window);
        
        sprite.setPosition(mousePos);
        
        std::cout << prefix << ": (x=" << static_cast<int>(mousePos.x) 
                  << ", y=" << static_cast<int>(mousePos.y) << ")    \r";
        
        std::cout.flush(); 
    }

    void drawBoundingBox(sf::RenderWindow& window, const sf::Sprite& sprite, sf::Color color) {
        sf::FloatRect bounds = sprite.getGlobalBounds();
        sf::RectangleShape box;
        box.setPosition(bounds.left, bounds.top);
        box.setSize(sf::Vector2f(bounds.width, bounds.height));
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineColor(color);
        box.setOutlineThickness(1.f);
        window.draw(box);
    }

    bool isMouseOver(const sf::RenderWindow& window, const sf::Sprite& sprite) {
        sf::Vector2f mousePos = getMouseWorldPosition(window);
        return sprite.getGlobalBounds().contains(mousePos);
    }

    float getDistance(sf::Vector2f v1, sf::Vector2f v2) {
        float dx = v2.x - v1.x;
        float dy = v2.y - v1.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    float getVectorLength(sf::Vector2f v) {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    sf::Vector2f normalizeVector(sf::Vector2f v) {
        float len = getVectorLength(v);
        if (len != 0) {
            return v / len;
        }
        return v;
    }

    void testSpritePosition(sf::Sprite& sprite, sf::RenderWindow& window, const std::string& prefix)
    {
        sprite.setOrigin(0,0);
        debugFollowMouse(sprite, window, prefix);/**/
    }
}

