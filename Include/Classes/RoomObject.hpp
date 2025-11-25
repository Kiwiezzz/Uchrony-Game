#pragma once

#include "Classes/Entity.hpp"

namespace sf { class RenderWindow; }

class RoomObject : public Entity
{
public:

    

    /** @brief Muestra un texto de descripción del objeto en un cuadro flotante (algo así como un diálogo).
     *  Si no tiene descripción, no muestra nada.
     *  @return Una ventana de diálogo con el texto del objeto.
     */
    void showText();

    /// @brief Renderiza el objeto en la ventana
    /// @param window Referencia a la ventana donde se dibuja el objeto
    void draw(sf::RenderWindow& window);
};