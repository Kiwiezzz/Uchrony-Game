#pragma once
// [DEPRECATED] Esta clase es un remanente del sistema antiguo.
// Usar GenericScene y SceneRegistry para nuevas escenas.
#include "Core/GameState.hpp"
#include <SFML/Graphics.hpp>

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
#include "Entities/NPC.hpp"
#include "Utils/NavGrid.hpp"
#include "Utils/Pathfinder.hpp"
#include "Utils/Collision.hpp"


class Screen1 : public GameState {
private:
    // --- AQUÍ VAN LAS VARIABLES QUE ANTES ESTABAN SUELTAS EN EL MAIN ---
    
    
    //Variables:
    bool isDebugPlacing;

    // Variables específicas de esta escena (no del GameManager)
    SpriteAsset background;
    ImageAsset collision;
    NavGrid navGrid;
    Player player;
    Pathfinder pathfinder;

    NPC npc; // Declaración del NPC

     // tamaño de celda en píxeles
    

    std::map<std::string, SpriteAsset> objects;
    
    // Inventory inventory; // Removed to use singleton
    std::map<std::string, TextureAsset> items;
    sf::SoundBuffer ocarinaBuffer;
    sf::Sound ocarinaSound;
    // draggingItem y draggingFrom ahora están en GameManager singleton

public:
    Screen1();

    void init() override;

    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    
    void update(sf::Time dt) override;
    
    void render(sf::RenderWindow& window) override;

};