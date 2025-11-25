#pragma once

#include <unordered_map>
#include <optional>


#include "Core/GameState.hpp"
#include "Classes/Room.hpp"
#include "Utils/Pathfinder.hpp"
#include "Classes/ObjectRoom.hpp"

using namespace std;

class Past : public GameState
{
protected:
    sf::Texture texturaJugador; // ¡IMPORTANTE! Las texturas deben ser miembros de la clase
    sf::Sprite spriteJugador;

    unordered_map<string, Room> rooms; //Tabla hash con las habitaciones
    Room* currentRoom;

    //Faltan cosas

    //Pathfinder pathfinder;

    //sf::Texture slotTex;
    //Inventory inventory;
    //std::map<std::string, TextureAsset> items;
    //std::optional<Item> draggingItem;
    //int draggingFrom;
};



