#ifndef GAMEUTILITIES_HPP
#define GAMEUTILITIES_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

/*
 * GameUtilities.hpp
 * Un conjunto de funciones de utilidad "solo-encabezado" para SFML.
 * Inclúyelo en tu main.cpp con #include "GameUtilities.hpp"
 *
 * Todas las funciones están dentro del namespace 'GameUtils', así que
 * llámalas usando: GameUtils::nombreFuncion(...)
 *
 * Usamos 'inline' para evitar errores de "múltiples definiciones"
 * al incluir este archivo en varios lugares.
 */
namespace GameUtils {

    /**
     * @brief Obtiene la posición del mouse como un Vector2f (coordenadas del mundo).
     * Simplifica la conversión de sf::Mouse::getPosition a coordenadas float.
     * @param window La ventana activa de SFML.
     * @return sf::Vector2f con la posición (x, y) del mouse.
     */
    inline sf::Vector2f getMouseWorldPosition(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }

    /**
     * @brief Dibuja un marcador visual (círculo) en una posición específica.
     * ¡Perfecto para tu solicitud de "marcar la posición donde doy click"!
     * @param window La ventana donde se dibujará.
     * @param position La posición (x, y) donde dibujar el marcador.
     * @param color El color del marcador (por defecto, Rojo).
     * @param radius El radio del círculo (por defecto, 5 píxeles).
     */
    inline void markPosition(sf::RenderWindow& window, sf::Vector2f position, sf::Color color = sf::Color::Red, float radius = 5.f) {
        sf::CircleShape marker(radius);
        marker.setOrigin(radius, radius); // Centra el círculo en la posición
        marker.setPosition(position);
        marker.setFillColor(sf::Color::Transparent);
        marker.setOutlineColor(color);
        marker.setOutlineThickness(2.f);
        window.draw(marker);
    }

    /**
     * @brief Dibuja el rectángulo de colisión (Bounding Box) de un sprite.
     * Increíblemente útil para depurar colisiones e interacciones.
     * @param window La ventana donde se dibujará.
     * @param sprite El sprite del cual obtener el GlobalBounds.
     * @param color El color del rectángulo (por defecto, Verde).
     */
    inline void drawBoundingBox(sf::RenderWindow& window, const sf::Sprite& sprite, sf::Color color = sf::Color::Green) {
        sf::FloatRect bounds = sprite.getGlobalBounds();
        sf::RectangleShape box;
        box.setPosition(bounds.left, bounds.top);
        box.setSize(sf::Vector2f(bounds.width, bounds.height));
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineColor(color);
        box.setOutlineThickness(1.f);
        window.draw(box);
    }

    /**
     * @brief Comprueba si el mouse está actualmente sobre un sprite.
     * Usa la detección de 'getGlobalBounds().contains()'.
     * @param window La ventana activa.
     * @param sprite El sprite con el que se comprueba la colisión.
     * @return true si el mouse está sobre el sprite, false en caso contrario.
     */
    inline bool isMouseOver(sf::RenderWindow& window, const sf::Sprite& sprite) {
        sf::Vector2f mousePos = getMouseWorldPosition(window);
        return sprite.getGlobalBounds().contains(mousePos);
    }

    // --- Funciones de Matemáticas Vectoriales ---

    /**
     * @brief Calcula la distancia entre dos puntos (vectores).
     * @param v1 El primer punto.
     * @param v2 El segundo punto.
     * @return La distancia (float).
     */
    inline float getDistance(sf::Vector2f v1, sf::Vector2f v2) {
        float dx = v2.x - v1.x;
        float dy = v2.y - v1.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    /**
     * @brief Calcula la magnitud (longitud) de un vector.
     * @param v El vector.
     * @return La longitud (float).
     */
    inline float getVectorLength(sf::Vector2f v) {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    /**
     * @brief Normaliza un vector (lo convierte en un vector de longitud 1).
     * Útil para obtener solo la dirección.
     * @param v El vector a normalizar.
     * @return El vector normalizado.
     */
    inline sf::Vector2f normalizeVector(sf::Vector2f v) {
        float len = getVectorLength(v);
        if (len != 0) {
            return v / len;
        }
        return v; // Devuelve el vector cero si la longitud es cero
    }

} // fin del namespace GameUtils

#endif // GAMEUTILITIES_HPP