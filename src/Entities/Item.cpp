#include "Entities/Item.hpp"
#include <iostream>

Item::Item(int id, const sf::Texture& tex, float scale)
    : m_id(id), m_texture(tex)
{
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(scale, scale);
    m_sprite.setOrigin(0.f, 0.f);
}

Item::Item(const Item& copy) :
    m_texture(copy.m_texture), m_id(copy.m_id), m_sprite(copy.m_sprite)
{
    m_sprite.setTexture(m_texture);
}

void Item::onClick() const {
    std::cout << "Item clicked id=" << m_id << std::endl;
}

Item& Item::operator=(const Item& other)
{
    m_id = other.m_id;
    m_texture = other.m_texture;
    m_sprite = other.m_sprite;
    m_sprite.setTexture(m_texture);
    return *this;
}