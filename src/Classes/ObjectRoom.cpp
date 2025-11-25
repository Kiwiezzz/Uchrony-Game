#include "Classes/ObjectRoom.hpp"
#include <iostream> // Opcional, para debug con cout

void ObjectRoom::init()
{
    // Aquí inicializas tu sprite, texturas, posición, etc.
    // Ej: sprite.setPosition(100, 100);
}

void ObjectRoom::handleEvent(sf::Event event)
{
    // Aquí detectas si le hacen clic al objeto, por ejemplo
    /*
    if (event.type == sf::Event::MouseButtonPressed) {
        if (getBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            showText();
        }
    }
    */
}

void ObjectRoom::update(sf::Time dt)
{
    // Lógica frame a frame (animaciones, flotar, etc.)
}

void ObjectRoom::draw(sf::RenderWindow& window)
{
    // Dibuja el objeto. 
    // Asumo que tienes un 'sprite' o similar heredado de Entity o definido aquí
    // window.draw(sprite);
}

void ObjectRoom::showText()
{
    // Aquí iría la lógica para llamar a tu sistema de diálogos
    // Ej: GameManager::getInstance().getDialogueSystem().show("Es una maceta vieja.");
    std::cout << "Muestrando descripción del objeto..." << std::endl;
}


ObjectRoom::ObjectRoom(const std::string& path) : Entity(path)
{
    
}

ObjectRoom::ObjectRoom(const Entity& entityCopy) : Entity(*this)
{

}