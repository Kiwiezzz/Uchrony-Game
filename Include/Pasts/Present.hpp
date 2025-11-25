#pragma once

#include "Classes/Past.hpp"

class Present : protected Past
{
    

public:
    void init() override;

    
    /// @brief Se encarga de manejar los eventos (inputs) que suceden, por lo general mas a nivel global
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    
    /// @brief 
    /// @param dt 
    void update(sf::Time dt) override;

    void render(sf::RenderWindow& window) override;
};