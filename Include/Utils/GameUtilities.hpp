#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace GameUtils {

    /**
     * @brief Obtiene la posición del mouse como un Vector2f (coordenadas del mundo).
     */
    sf::Vector2f getMouseWorldPosition(const sf::RenderWindow& window);

    /**
     * @brief Dibuja un marcador visual (círculo) en una posición específica.
     */
    void markPosition(sf::RenderWindow& window, sf::Vector2f position, sf::Color color = sf::Color::Red, float radius = 5.f);

    // Registro de posición en consola para depuración
    void logPosition(sf::Vector2f position, const std::string& prefix = "Position");

    /* Mueve un sprite a la posicion del mouse y muestra coordenadas */
    void debugFollowMouse(sf::Sprite& sprite, sf::RenderWindow& window, const std::string& prefix = "Debug Pos");

    // Dibuja el bounding box de un sprite para depuración (hitbox visual)
    void drawBoundingBox(sf::RenderWindow& window, const sf::Sprite& sprite, sf::Color color = sf::Color::Green);

    /**
     * @brief Comprueba si el mouse está actualmente sobre un sprite.
     */
    bool isMouseOver(const sf::RenderWindow& window, const sf::Sprite& sprite);

    // --- Funciones vectoriales básicas ---

    // Devuelve la distancia entre dos vectores
    float getDistance(sf::Vector2f v1, sf::Vector2f v2);

    // Devuelve la longitud (Magnitud) de un vector
    float getVectorLength(sf::Vector2f v);

    /**
     * @brief Normaliza un vector (lo convierte en un vector de longitud 1).
     */
    sf::Vector2f normalizeVector(sf::Vector2f v);

}