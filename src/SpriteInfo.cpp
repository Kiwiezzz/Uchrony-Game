#include "SpriteInfo.hpp"

#include <iostream>

SpriteInfo::SpriteInfo() : path(""), texture(std::make_shared<sf::Texture>()), sprite() {}

SpriteInfo::SpriteInfo(const std::string& path)
    : path("") , texture(std::make_shared<sf::Texture>()), sprite()
{
    new_path_and_update(path);
}

void SpriteInfo::new_path_and_update(const std::string& p)
{
    path = p;
    texture = std::make_shared<sf::Texture>();

    if (!texture->loadFromFile(path)) {
        std::cerr << "Error: no se pudo cargar texture '" << path << "'" << std::endl;
    }

    sprite = sf::Sprite(*texture);
}