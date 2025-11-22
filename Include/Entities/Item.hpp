#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Item {
public:
    Item() = default;
    // Construye un item a partir de una textura (la textura debe mantenerse viva fuera)
    // `scale` permite ajustar la escala inicial del sprite (lo puedes modificar después)
    Item(int id, const sf::Texture& tex, float scale = 1.f);

    int id() const { return m_id; }
    const sf::Sprite& sprite() const { return m_sprite; }
    sf::Sprite& sprite() { return m_sprite; }

    // Evento que se dispara al hacer click en el item (por ahora solo devuelve id)
    virtual void onClick() const;

private:
    int m_id = -1;
    sf::Sprite m_sprite;
};
