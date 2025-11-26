#include "Pasts/Past0.hpp"

void Past0::init()
{
    auto& firstRoom = rooms["first"] = Room();
    
    
    firstRoom.setBackground("assets/textures/suelo.png");
    firstRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    firstRoom.getBackground().sprite.setPosition(0, 0);

    firstRoom.setCollisionAndGrid("assets/textures/escenario_colision.png");
    
    // Carga de objetos
    
    ObjectRoom* mesa = new ObjectRoom("assets/textures/mesa.png");
    mesa->sprite.setPosition(397, 494);
    mesa->sprite.setOrigin(float(mesa->texture.getSize().x) / 2.f, float(mesa->texture.getSize().y));
    mesa->setlayer(0);
    firstRoom.addEntity("mesa", mesa);
    
    ObjectRoom* mesa2 = new ObjectRoom("assets/textures/mesa_2.png");
    mesa2->sprite.setPosition(673, 284);
    mesa2->sprite.setOrigin(float(mesa2->texture.getSize().x) / 2.f, float(mesa2->texture.getSize().y));
    mesa2->setlayer(0);
    firstRoom.addEntity("mesa2", mesa2);

    ObjectRoom* botella = new ObjectRoom("assets/textures/botella.png");
    botella->sprite.setPosition(597, 185);
    botella->setlayer(1); // la botella debe renderizarse por encima de la mesa
    firstRoom.addEntity("botella", botella);
    


    NPC npc;
    npc.init("assets/textures/npc_spritesheet.png", Vec2f(400.f, 300.f), true);
    //npc.getSprite().setScale(2.0f, 2.0f);
    //npc.setupAnimations(); // Private now
    npc.addAnimation("Posicion_Espalda", 0, 1, 2.0f, false, 2);
    npc.addAnimation("Posicion_Espalda2", 0, 1, 2.0f, false, 5);
    //row(r), frameCount(fc), duration(d), loop(l), startColumn(sc)
    
    firstRoom.addNpc("npc", npc);
    
    
    currentRoom = &rooms["first"];
    /*
    //El jugador está en GameManager
    auto& GM = GameManager::get();

    GM.getPlayer().setPosition(400.f, 300.f); //Posicion Inicial
    GM.getPlayer().getSprite().setScale(2.0f, 2.0f);
    */

    
    // Añadir items de ejemplo: botella, guitarra, lentes, ocarina
    // Cargar texturas de items
    
    // Cargar sonido de la ocarina (se usará al hacer click izquierdo sobre el item)
    /*
    if (!ocarinaBuffer.loadFromFile("assets/sounds/ocarina.mp3")) {
        std::cerr << "Warning: no se cargo assets/sounds/ocarina.mp3" << std::endl;
    }
    
    ocarinaSound.setBuffer(ocarinaBuffer);*/
    /*TextureAsset guitarra("assets/textures/Guitarra.png");
    TextureAsset lentes("assets/textures/lentes.png");
    TextureAsset ocarina("assets/textures/Ocarina.png");

    Item bottleItem(1, botella->texture);
    bottleItem.sprite().setScale(0.1f, 0.1f); // Escala personalizada para la botella
    Item guitarItem(2, guitarra.texture);
    guitarItem.sprite().setScale(0.05f, 0.05f);
    Item lentesItem(3, lentes.texture);
    lentesItem.sprite().setScale(0.05f, 0.05f);
    Item ocarinaItem(4, ocarina.texture);
    ocarinaItem.sprite().setScale(0.1f, 0.1f);

    GameManager::get().getInventory().insertAt(0, bottleItem);
    GameManager::get().getInventory().insertAt(1, guitarItem);
    GameManager::get().getInventory().insertAt(2, lentesItem);
    GameManager::get().getInventory().insertAt(3, ocarinaItem);
    
    
    //isDebugPlacing = false; // Modo para colocar y seguir objetos con el mouse*/
}


void Past0::handleEvent(sf::Event& event, sf::RenderWindow& window)
{

}

void Past0::update(sf::Time dt)
{

}

void Past0::render(sf::RenderWindow& window)
{
    currentRoom->render(window);
}