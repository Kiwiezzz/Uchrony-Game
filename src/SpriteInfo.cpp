#include "SpriteInfo.hpp"

SpriteInfo::SpriteInfo() : path(""), texture(), sprite() {}

SpriteInfo::SpriteInfo(const std::string& path) 
{
    new_path_and_update(path);
}

void SpriteInfo::new_path_and_update(const std::string& p)
{
    path = p;

    if (!texture.loadFromFile(path)) {}
    sprite = sf::Sprite(texture);
}