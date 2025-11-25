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
#include "Entities/Inventory.hpp"

class Screen1 : public GameState {
private:
    // --- AQUÍ VAN LAS VARIABLES QUE ANTES ESTABAN SUELTAS EN EL MAIN ---
    sf::Texture texturaJugador; // ¡IMPORTANTE! Las texturas deben ser miembros de la clase
    sf::Sprite spriteJugador;
    
    //Variables:
    bool isDebugPlacing;

    SpriteAsset background;
    ImageAsset collision;

    Player player;
    NPC npc; // Declaración del NPC

    NavGrid navGrid; // tamaño de celda en píxeles
    Pathfinder pathfinder;

    std::map<std::string, SpriteAsset> objects;
    sf::Texture slotTex;
    // Inventory inventory; // Removed to use singleton
    std::map<std::string, TextureAsset> items;
    sf::SoundBuffer ocarinaBuffer;
    sf::Sound ocarinaSound;
    std::optional<Item> draggingItem;
    int draggingFrom;

public:
    Screen1();

    void init() override;

    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    
    void update(sf::Time dt) override;
    
    void render(sf::RenderWindow& window) override;

};