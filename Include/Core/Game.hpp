#pragma once


#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <optional>
#include <stdexcept>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Utils/GameUtilities.hpp"
#include "Utils/Assets.hpp"
#include "Entities/Player.hpp"
#include "Utils/NavGrid.hpp"
#include "Utils/Pathfinder.hpp"
#include "Utils/Collision.hpp"
#include "Entities/Inventory.hpp"


class Game
{
public:
    /// @brief Constructor
    Game();

    /// @brief Corre el juego
    void run();

private:
    void handleEvents();    //1. Procesar eventos
    void update();          //2. Actualizar
    void render();          //3. Renderizar


//Variables
    sf::RenderWindow mWindow;


//DESASTRE

    sf::Clock clock;
    bool isDebugPlacing;

    SpriteAsset background;
    ImageAsset collision;

    Player player;

    NavGrid navGrid; // tamaño de celda en píxeles
    Pathfinder pathfinder;

    std::map<std::string, SpriteAsset> objects;
    sf::Texture slotTex;
    Inventory inventory;

    std::map<std::string, TextureAsset> items;
    sf::SoundBuffer ocarinaBuffer;
    sf::Sound ocarinaSound;
    std::optional<Item> draggingItem;
    int draggingFrom;
};