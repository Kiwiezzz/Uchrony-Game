#pragma once

#include "Core/GameState.hpp"
#include "Utils/Assets.hpp"

class Screen : public GameState
{
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
    Inventory inventory;

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

