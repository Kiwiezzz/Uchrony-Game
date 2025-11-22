#ifndef SPRITEINFO_HPP
#define SPRITEINFO_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

struct SpriteInfo {
    std::string path;
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;


    SpriteInfo();

    SpriteInfo(const std::string& path);

    void new_path_and_update(const std::string& newPath);
};

#endif /* SPRITEINFO_HPP */