#include "Pasts/PastExample.hpp"
#include <iostream>

void PastExample::init()
{
    auto& firstRoom = rooms["first"] = Room();
    
    
    firstRoom.setBackground("assets/textures/suelo.png");
    firstRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    firstRoom.getBackground().sprite.setPosition(0, 0);

    firstRoom.setCollisionAndGrid("assets/textures/escenario_colision.png");
    
    // Setear el puntero a Game en el room para permitir cambios de estado
    firstRoom.setGame(this->game);
    
    // Carga de objetos
    
    auto mesa = std::make_unique<ObjectRoom>("assets/textures/mesa.png");
    mesa->sprite.setPosition(397, 494);
    mesa->sprite.setOrigin(float(mesa->texture.getSize().x) / 2.f, float(mesa->texture.getSize().y));
    mesa->setlayer(0);
    firstRoom.addEntity("mesa", std::move(mesa));
    
    auto mesa2 = std::make_unique<ObjectRoom>("assets/textures/mesa_2.png");
    mesa2->sprite.setPosition(673, 284);
    mesa2->sprite.setOrigin(float(mesa2->texture.getSize().x) / 2.f, float(mesa2->texture.getSize().y));
    mesa2->setlayer(0);
    firstRoom.addEntity("mesa2", std::move(mesa2));

    auto botella = std::make_unique<ObjectRoom>("assets/textures/botella.png");
    botella->sprite.setPosition(597, 185);
    botella->setlayer(1); // la botella debe renderizarse por encima de la mesa
    firstRoom.addEntity("botella", std::move(botella));
    


    NPC npc;
    npc.init("assets/textures/npc_spritesheet.png", Vec2f(400.f, 300.f), true);
    //npc.getSprite().setScale(2.0f, 2.0f);
    //npc.setupAnimations(); // Private now
    npc.addAnimation("Posicion_Espalda", 0, 1, 2.0f, false, 2);
    npc.addAnimation("Posicion_Espalda2", 0, 1, 2.0f, false, 5);
    //row(r), frameCount(fc), duration(d), loop(l), startColumn(sc)
    
    firstRoom.addNpc("npc", npc);
    
    // Define door triggers
    doorTriggers["first"] = sf::FloatRect(360.f, 50.f, 80.f, 120.f);

    // Setup second room
    auto& secondRoom = rooms["second"] = Room();
    secondRoom.setBackground("assets/textures/suelo.png");
    secondRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    secondRoom.getBackground().sprite.setPosition(0, 0);
    secondRoom.setCollisionAndGrid("assets/textures/escenario_colision.png");
    secondRoom.setGame(this->game);

    // Add objects to second room (same tables)
    auto mesa_r2 = std::make_unique<ObjectRoom>("assets/textures/mesa.png");
    mesa_r2->sprite.setPosition(397, 494);
    mesa_r2->sprite.setOrigin(float(mesa_r2->texture.getSize().x) / 2.f, float(mesa_r2->texture.getSize().y));
    mesa_r2->setlayer(0);
    secondRoom.addEntity("mesa", std::move(mesa_r2));

    auto mesa2_r2 = std::make_unique<ObjectRoom>("assets/textures/mesa_2.png");
    mesa2_r2->sprite.setPosition(673, 284);
    mesa2_r2->sprite.setOrigin(float(mesa2_r2->texture.getSize().x) / 2.f, float(mesa2_r2->texture.getSize().y));
    mesa2_r2->setlayer(0);
    secondRoom.addEntity("mesa2", std::move(mesa2_r2));

    doorTriggers["second"] = sf::FloatRect(360.f, 50.f, 80.f, 120.f);
      
    currentRoom = &rooms["first"];
    
    // El jugador está en GameManager
    auto& GM = GameManager::get();

    GM.getPlayer().setPosition(400.f, 300.f); //Posicion Inicial
    GM.getPlayer().getSprite().setScale(2.0f, 2.0f);
}


void PastExample::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    // Manejo de click izquierdo en inventario (onClick de items)
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Primero verificar si se hizo click en el inventario
            sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);
            
            int uiIdx = GameManager::get().getInventory().indexAtScreenPos(mouseWinPos, window);
            if (uiIdx >= 0) {
                const Item* it = GameManager::get().getInventory().itemAt((unsigned)uiIdx);
                if (it) {
                    it->onClick();
                    // TODO: Reproducir sonidos según el item (ej: ocarina)
                }
                return; // No procesar más eventos si se hizo click en UI
            }
            
            // Si no se hizo click en UI, delegar al room actual
            
            // Check door trigger
            sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mouseWinPos);
            std::string currentRoomName = "";
            if (currentRoom == &rooms["first"]) currentRoomName = "first";
            else if (currentRoom == &rooms["second"]) currentRoomName = "second";

            if (!currentRoomName.empty() && doorTriggers.count(currentRoomName) && doorTriggers[currentRoomName].contains(mouseWorldPos)) {
                
                Vec2f targetPos(400.f, 180.f);
                Room* nextRoomPtr = nullptr;

                if (currentRoomName == "first") {
                    nextRoomPtr = &rooms["second"];
                } else {
                    nextRoomPtr = &rooms["first"];
                }
                
                auto& navGrid = currentRoom->getNavGrid();
                Point start = navGrid.worldToGrid(GameManager::get().getPlayer().getPosition());
                Point end = navGrid.worldToGrid(targetPos);
                
                if (navGrid.isWalkable(end)) {
                     std::vector<Point> path = pathfinder.findPath(navGrid, start, end);
                     if (!path.empty()) {
                         GameManager::get().getPlayer().setPath(path, navGrid);
                         m_pendingRoomSwitch = true;
                         m_pendingNextRoom = nextRoomPtr;
                         std::cout << "Walking to door..." << std::endl;
                     } else {
                         std::cout << "No path to door!" << std::endl;
                     }
                } else {
                    std::cout << "Door target not walkable!" << std::endl;
                }
                return;
            }

            // If we clicked somewhere else (and not on UI), cancel the pending switch
            m_pendingRoomSwitch = false;
            m_pendingNextRoom = nullptr;

            if (currentRoom) {
                currentRoom->handleEvent(event, window);
            }
        }
    }

    // CLICK DERECHO: iniciar drag de items en inventario
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Right) {
            sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);

            int uiIdx = GameManager::get().getInventory().indexAtScreenPos(mouseWinPos, window);
            if (uiIdx >= 0) {
                draggingItem = GameManager::get().getInventory().pickAt(uiIdx);
                if (draggingItem) draggingFrom = uiIdx;
                return;
            }
        }
    }

    // SOLTAR CLICK DERECHO: finalizar drag de items
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Right && draggingItem) {
            sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);
            int idx = GameManager::get().getInventory().indexAtScreenPos(mouseWinPos, window);
            if (idx >= 0) {
                GameManager::get().getInventory().insertAt(idx, *draggingItem);
            } else {
                GameManager::get().getInventory().insertAt(draggingFrom >= 0 ? (unsigned)draggingFrom : GameManager::get().getInventory().size(), *draggingItem);
            }
            draggingItem.reset();
            draggingFrom = -1;
        }
    }
}

void PastExample::update(sf::Time dt)
{
    currentRoom->update(dt);
    GameManager::get().getPlayer().update(dt);

    // Check if we reached the door
    if (m_pendingRoomSwitch && !GameManager::get().getPlayer().isMoving()) {
        if (m_pendingNextRoom) {
            currentRoom = m_pendingNextRoom;
            std::cout << "Arrived at door. Switched room!" << std::endl;
        }
        m_pendingRoomSwitch = false;
        m_pendingNextRoom = nullptr;
    }
}

void PastExample::render(sf::RenderWindow& window)
{
    currentRoom->render(window);
    // El jugador ahora se renderiza dentro de currentRoom->render() para respetar el Y-Sorting
    
    // DIBUJO UI (inventario) en vista por defecto para que quede fija en pantalla
    auto prevView = window.getView();
    window.setView(window.getDefaultView());
    sf::Vector2u ws = window.getSize();
    float margin = 8.f;
    // Usar la altura de slot ya escalada para posicionar correctamente el inventario
    GameManager::get().getInventory().setBasePosition({ margin, float(ws.y) - margin - float(GameManager::get().getInventory().displaySlotHeight()) });
    GameManager::get().getInventory().draw(window);

    // Dibujar item arrastrado bajo el mouse
    if (draggingItem) {
        sf::Vector2i mp = sf::Mouse::getPosition(window);
        // SOLO dibujamos el sprite del item (no el fondo del slot)
        sf::Sprite s = draggingItem->sprite();
        sf::FloatRect gb = s.getGlobalBounds();
        s.setPosition(float(mp.x) - gb.width/2.f, float(mp.y) - gb.height/2.f);
        window.draw(s);
    }

    window.setView(prevView);
}