#include "Classes/Room.hpp"
#include <SFML/Graphics.hpp> // Incluimos para definir sf::RenderWindow y sf::Event
#include <iostream>          // Opcional, pero se mantiene por si acaso

// Implementaciones vacías. La lógica es: "Esta función existe, pero no hace nada aún".

void Room::init()
{
    // LÓGICA DE INICIALIZACIÓN FUTURA
}

void Room::handleEvent(sf::Event event)
{
    // LÓGICA DE INPUT FUTURA
}

void Room::update(sf::Time dt)
{
    // LÓGICA DE ACTUALIZACIÓN FUTURA
}

void Room::render(sf::RenderWindow& window)
{
    //window.draw(background.sprite);
    for (auto& entity : entities) {
        window.draw(entity.second->sprite);
    }

    /*for (auto& npc : npcs) {
        if(!npc.second)
            npc.second->render(window);
    }*/
}



void Room::setBackground(std::string path)
{
    background.new_path_and_update(path);
}

void Room::setCollisionAndGrid(std::string path)
{
    collision.new_path_and_update(path);
    navGrid = NavGrid(16);
    if (!navGrid.buildFromImage(collision.image)) {
        std::cerr << "Error: NavGrid::buildFromImage falló. Imagen inválida o tamaño incorrecto." << std::endl;
        //DEBERÍA CERRARSE
    }
}


void Room::addEntity(const std::string& name, Entity* entity)
{
    entities[name] = entity;
}

void Room::addNpc(const std::string& name, NPC& npc){
    npcs[name] = npc;
}

SpriteAsset& Room::getBackground()
{
    return background;
}

Entity& Room::getEntity(std::string name)
{
    // Nota: Esto lanzará una excepción si la key no existe.
    // Deberías manejarlo o usar find() si no estás seguro.
    return *entities.at(name);
}

NPC& Room::getNpc(std::string name)
{
    return npcs.at(name);
}
