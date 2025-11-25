#pragma once

#include "Classes/Entity.hpp"
#include <SFML/Graphics.hpp> // Necesario para que reconozca sf::Event y sf::Time

class ObjectRoom : public Entity
{
public:
    ObjectRoom(const std::string& path);

    ObjectRoom(const Entity& entityCopy);

    // Solo declaramos las funciones, sin el cuerpo "{}" y sin "ObjectRoom::"
    void init();
    
    // NOTA: Entity suele pedir handleInput por referencia (sf::Event& event)
    // pero lo dejo como lo pusiste (por valor) por si acaso.
    void handleEvent(sf::Event event); 

    void update(sf::Time dt) override;
    
    // Dejé solo un draw (el override) porque el otro era un duplicado
    void draw(sf::RenderWindow& window) override;

    /** @brief Muestra un texto de descripción del objeto. */
    void showText();
};