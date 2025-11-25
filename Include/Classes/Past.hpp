#pragma once

#include <unordered_map>
#include <optional>


#include "Core/GameState.hpp"
#include "Classes/Room.hpp"
#include "Utils/Pathfinder.hpp"

using namespace std;

class Past : public GameState
{
    sf::Texture texturaJugador; // ¡IMPORTANTE! Las texturas deben ser miembros de la clase
    sf::Sprite spriteJugador;

    unordered_map<string, Room> rooms; //Tabla hash con las habitaciones

    Pathfinder pathfinder;

    //sf::Texture slotTex;
    //Inventory inventory;
    //std::map<std::string, TextureAsset> items;
    //std::optional<Item> draggingItem;
    //int draggingFrom;

public:
    void init() override;

    
    /// @brief Se encarga de manejar los eventos (inputs) que suceden, por lo general mas a nivel global
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    
    /// @brief 
    /// @param dt 
    void update(sf::Time dt) override;

    void render(sf::RenderWindow& window) override;
};



