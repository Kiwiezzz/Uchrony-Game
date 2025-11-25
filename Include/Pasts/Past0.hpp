#pragma once
// [DEPRECATED] Esta clase es un remanente del sistema antiguo.
// Usar GenericScene y SceneRegistry para nuevas escenas.

#include "Classes/Past.hpp"
#include "Entities/NPC.hpp"
#include "GameManager.hpp"

class Past0 : public Past //:GameState
{
public:
    /// @brief carga los diferentes rooms
    void init() override;

    
    /// @brief Se encarga de manejar los eventos (inputs) que suceden, por lo general mas a nivel global
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    
    /// @brief 
    /// @param dt 
    void update(sf::Time dt) override;

    void render(sf::RenderWindow& window) override;
};