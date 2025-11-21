#include "Entities/Item.hpp"
#include <iostream>

Item::Item(int id, const sf::Texture& tex, float scale)
    : m_id(id)
{
    m_sprite.setTexture(tex);
    m_sprite.setScale(scale, scale);
    m_sprite.setOrigin(0.f, 0.f);
}

void Item::onClick() const {
    std::cout << "Item clicked id=" << m_id << std::endl;
}
