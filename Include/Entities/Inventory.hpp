#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <optional>
#include "Entities/Item.hpp"

class Inventory {
public:
    Inventory() = default;

    void Init(const std::string& slotTexturePath, unsigned slotW, unsigned slotH,
              unsigned capacity = 4, float spacing = 8.f);

    void setDisplayScale(float s) { m_displayScale = s; }
    
    
    
    void draw(sf::RenderWindow& window) const;
    


    unsigned capacity() const;
    unsigned size() const;

    void insertAt(unsigned index, const Item& item);
    std::optional<Item> pickAt(unsigned index);
    void removeAt(unsigned index);
    void move(unsigned fromIndex, unsigned toIndex);

    int indexAtScreenPos(sf::Vector2i mousePos, const sf::RenderWindow& window) const;
    void setBasePosition(sf::Vector2f basePos);
    // Dibuja el fondo de un slot (la textura completa) en la posición top-left indicada
    void drawSlotBackgroundAt(sf::RenderWindow& window, sf::Vector2f topLeft) const;
    unsigned slotWidth() const { return m_slotW; }
    unsigned slotHeight() const { return m_slotH; }
    float displaySlotWidth() const { return float(m_slotW) * m_displayScale; }
    float displaySlotHeight() const { return float(m_slotH) * m_displayScale; }

    // Acceso no destructivo al item en una ranura (devuelve nullptr si vacía)
    const Item* itemAt(unsigned index) const;
    Item* itemAt(unsigned index);

private:
    sf::Vector2f slotPosition(unsigned index) const;

    std::list<Item> m_items;
    sf::Texture m_slotTexture; // atlas with N slots horizontally
    unsigned m_slotW;
    unsigned m_slotH;
    unsigned m_capacity;
    float m_spacing;
    sf::Vector2f m_basePos; // top-left of the first slot
    float m_displayScale = 0.6f; // escala visual por defecto (60%)
};

