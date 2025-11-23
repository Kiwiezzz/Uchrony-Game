#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

struct SpriteAsset {
    std::string path;
    sf::Texture texture;
    sf::Sprite sprite;


    SpriteAsset() : 
        path(""), texture(), sprite()
    {}

    SpriteAsset(const std::string& path)
        : SpriteAsset()
    {
        new_path_and_update(path);
    }

    void new_path_and_update(const std::string& newPath)
    {   
        path = newPath;

        if (!texture.loadFromFile(path)) {
            std::cerr << "Error: no se pudo cargar texture '" << newPath << "'" << std::endl;
        }

        sprite = sf::Sprite(texture);
    }
};







struct ImageAsset {
    std::string path;
    sf::Image image;


    ImageAsset() : 
        path(""), image()
    { }

    ImageAsset(const std::string& path)
        : ImageAsset()
    {
        new_path_and_update(path);
    }

    void new_path_and_update(const std::string& newPath)
    {
        path = newPath;
        if (!image.loadFromFile(newPath)) {
            std::cerr << "Error: no se pudo cargar image '" << newPath << "'" << std::endl;
        }
    }
};





struct TextureAsset
{
    std::string path;
    sf::Texture texture;

    TextureAsset() : 
        path(""), texture()
    { }

    TextureAsset(const std::string& path)
        : TextureAsset()
    {
        new_path_and_update(path);
    }

    void new_path_and_update(const std::string& newPath)
    {
        path = newPath;
        if (!texture.loadFromFile(newPath)) {
            std::cerr << "Error: no se pudo cargar texture '" << newPath << "'" << std::endl;
        }
    }
};