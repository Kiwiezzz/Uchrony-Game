#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

struct SpriteAsset {
    std::string path;
    sf::Texture texture;
    sf::Sprite sprite; //Esto es una dirección de memoria, si simplemente la copias no servirá
    int layer; // Capa donde se renderiza

    /// @brief lo crea vacío
    SpriteAsset() : 
        path(""), texture(), sprite(), layer(0)
    {}

    /// @brief Crea el objeto y automaticamente carga la textura 
    /// y el sprite del path que le pasas
    /// @param newPath 
    SpriteAsset(const std::string& path)
        : SpriteAsset()
    {
        new_path_and_update(path);
    }

    /// @brief Carga la textura y el sprite del path que le pasas
    /// @param newPath 
    SpriteAsset(const SpriteAsset& spriteAsset) : 
        path(spriteAsset.path), texture(spriteAsset.texture), sprite(this->texture)
    {}

    void new_path_and_update(const std::string& newPath)
    {   
        path = newPath;

        if (!texture.loadFromFile(path)) {
            std::cerr << "Error: no se pudo cargar texture '" << newPath << "'" << std::endl;
        }

        sprite = sf::Sprite(texture);
    }
    
    //Funcion para mover el sprite
    void setPosition(float x, float y)
    {
        sprite.setPosition(x, y);
    }

    //Funcion para escalar el sprite
    void setScale(float scaleX, float scaleY)
    {
        sprite.setScale(scaleX, scaleY);
    }

    //Funcion para asignar la capa en que esta el sprite
    void setlayer(int newLayer)
    {
        layer = newLayer;
    }

    SpriteAsset& operator=(const SpriteAsset& other)
    {
        path = other.path;
        texture = other.texture;
        sprite = other.sprite;
        sprite = sf::Sprite(texture);

        return *this;
    }
};







struct ImageAsset {
    std::string path;
    sf::Image image;

    /// @brief Se crea vacío
    ImageAsset() : 
        path(""), image()
    { }

    /// @brief Carga automaticamente la imagen al construirse
    ImageAsset(const std::string& path)
        : ImageAsset()
    {
        new_path_and_update(path);
    }

    /// @brief Carga la imagen del path que le pasas
    /// @param newPath 
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

    /// @brief Lo crea vacío
    TextureAsset() : 
        path(""), texture()
    { }

    /// @brief Carga automaticamente la textura al construirse
    TextureAsset(const std::string& path)
        : TextureAsset()
    {
        new_path_and_update(path);
    }

    /// @brief Carga la textura del path que le pasas
    /// @param newPath 
    void new_path_and_update(const std::string& newPath)
    {
        path = newPath;
        if (!texture.loadFromFile(newPath)) {
            std::cerr << "Error: no se pudo cargar texture '" << newPath << "'" << std::endl;
        }
    }
};