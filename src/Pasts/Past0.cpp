#include "Pasts/Past0.hpp"
#include <iostream>

/**
 * @brief Inicializa todas las habitaciones (rooms) del Past0
 * 
 * Este método se llama una sola vez al inicio para configurar:
 * - Las 5 habitaciones del juego (cuarto, laboratorio, baño, patio, garage)
 * - Los triggers de puertas que permiten cambiar entre habitaciones
 * - La posición inicial del jugador
 */
void Past0::init()
{
    // ============================================================
    // HABITACIÓN 1: CUARTO (Bedroom)
    // ============================================================
    auto& firstRoom = rooms["first"] = Room();
    firstRoom.setBackground("assets/textures/Past0/Cuarto.png");
    firstRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    firstRoom.getBackground().sprite.setPosition(0, 0);
    // El mapa de colisiones define qué áreas son caminables (blanco) y cuáles no (negro)
    firstRoom.setCollisionAndGrid("assets/textures/Past0/Colisiones/cuarto_colision.png");
    firstRoom.setGame(this->game);

    // ============================================================
    // HABITACIÓN 2: LABORATORIO (Lab)
    // ============================================================
    auto& secondRoom = rooms["second"] = Room();
    secondRoom.setBackground("assets/textures/Past0/laboratorio.png");
    secondRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    secondRoom.getBackground().sprite.setPosition(0, 0);
    secondRoom.setCollisionAndGrid("assets/textures/Past0/Colisiones/laboratorio_colision.png");
    secondRoom.setGame(this->game);
    
    // --- Objetos decorativos en el laboratorio ---
    ObjectRoom* mesa = new ObjectRoom("assets/textures/mesa.png");
    mesa->sprite.setPosition(397, 494);
    mesa->sprite.setOrigin(float(mesa->texture.getSize().x) / 2.f, float(mesa->texture.getSize().y));
    mesa->setlayer(0);  // Layer 0 = detrás del jugador
    secondRoom.addEntity("mesa", mesa);
    
    // ============================================================
    // SISTEMA DE DEBUG DE SPRITES
    // ============================================================
    // Para posicionar un sprite con el sistema de debug:
    // 1. Descomenta las siguientes 2 líneas
    // 2. Compila y ejecuta el juego
    // 3. Presiona 'D' para activar modo debug
    // 4. El sprite seguirá al mouse
    // 5. La consola mostrará las coordenadas en tiempo real
    // 6. Copia las coordenadas y pégalas en setPosition()
    // 7. Comenta de nuevo las líneas y recompila
    //
    
    // ============================================================
    
    ObjectRoom* mesa2 = new ObjectRoom("assets/textures/mesa_2.png");
    mesa2->sprite.setPosition(667, 326);
    mesa2->sprite.setOrigin(float(mesa2->texture.getSize().x) / 2.f, float(mesa2->texture.getSize().y));
    mesa2->setlayer(0);
    secondRoom.addEntity("mesa2", mesa2);

    ObjectRoom* botella = new ObjectRoom("assets/textures/Past0/botella.png");
    botella->sprite.setPosition(597, 185);
    botella->setlayer(1);  // Layer 1 = delante del jugador
    secondRoom.addEntity("botella", botella);

    // ============================================================
    // HABITACIÓN 3: BAÑO (Bathroom)
    // ============================================================
    auto& bathroomRoom = rooms["bathroom"] = Room();
    bathroomRoom.setBackground("assets/textures/Past0/bath.png");
    bathroomRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    bathroomRoom.getBackground().sprite.setPosition(0, 0);
    bathroomRoom.setCollisionAndGrid("assets/textures/Past0/Colisiones/bath_colision.png");
    bathroomRoom.setGame(this->game);

    ObjectRoom* bathtub = new ObjectRoom("assets/textures/Past0/bathtub.png");
    bathtub->sprite.setPosition(0, 391);
    bathtub->setlayer(1);  // Layer 1 = delante del jugador
    bathroomRoom.addEntity("bathtub", bathtub);

    ObjectRoom* plant = new ObjectRoom("assets/textures/Past0/Plant.png");
    plant->sprite.setPosition(703, 386);
    plant->setlayer(1);  // Layer 1 = delante del jugador
    bathroomRoom.addEntity("plant", plant);

// ============================================================
    // HABITACIÓN 4: PATIO (Yard)
    // ============================================================
    auto& patioRoom = rooms["patio"] = Room();
    patioRoom.setBackground("assets/textures/Past0/yard.png");
    patioRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    patioRoom.getBackground().sprite.setPosition(0, 0);
    patioRoom.setCollisionAndGrid("assets/textures/Past0/Colisiones/yard_colision.png");
    patioRoom.setGame(this->game);

    // ============================================================
    // HABITACIÓN 5: GARAGE
    // ============================================================
    auto& garageRoom = rooms["garage"] = Room();
    garageRoom.setBackground("assets/textures/Past0/garage.png");
    garageRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    garageRoom.getBackground().sprite.setPosition(0, 0);
    garageRoom.setCollisionAndGrid("assets/textures/Past0/Colisiones/garage_colision.png");
    garageRoom.setGame(this->game);

    ObjectRoom* capo = new ObjectRoom("assets/textures/Past0/Capo.png");
    capo->sprite.setPosition(273, 204);
    capo->setlayer(1);  // Layer 1 = delante del jugador
    garageRoom.addEntity("capo", capo);

    ObjectRoom* esquina = new ObjectRoom("assets/textures/Past0/Esquina1.png");
    esquina->sprite.setPosition(26, 254);
    esquina->setlayer(1);  // Layer 1 = delante del jugador
    garageRoom.addEntity("esquina", esquina);

    ObjectRoom* esquina2 = new ObjectRoom("assets/textures/Past0/Esquina2.png");
    esquina2->sprite.setPosition(628, 261);
    esquina2->setlayer(1);  // Layer 1 = delante del jugador
    garageRoom.addEntity("esquina2", esquina2);


    //debugSprite = &esquina2->sprite;
    //debugSpriteName = "esquina2";

    // ============================================================
    // CONFIGURACIÓN DE TRIGGERS DE PUERTAS
    // ============================================================
    doorTriggers["first"] = sf::FloatRect(477.f, 446.f, 150.f, 120.f);
    doorTriggers["second_up"] = sf::FloatRect(358.f, 93.f, 80.f, 120.f);
    doorTriggers["second_right"] = sf::FloatRect(720.f, 250.f, 80.f, 600.f);
    doorTriggers["second_down"] = sf::FloatRect(230.f, 520.f, 400.f, 80.f);
    doorTriggers["second_left"] = sf::FloatRect(0.f, 250.f, 80.f, 600.f);
    doorTriggers["bathroom"] = sf::FloatRect(0.f, 250.f, 100.f, 300.f);
    doorTriggers["patio"] = sf::FloatRect(520.f, 100.f, 100.f, 110.f);
    doorTriggers["garage"] = sf::FloatRect(720.f, 250.f, 80.f, 80.f);
   
    currentRoom = &rooms["first"];
    
    auto& GM = GameManager::get();
    GM.getPlayer().setPosition(400.f, 300.f);
    GM.getPlayer().getSprite().setScale(2.0f, 2.0f);
}

void Past0::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
        isDebugPlacing = !isDebugPlacing;        std::cout << "Debug mode: " << (isDebugPlacing ? "ON" : "OFF") << std::endl;
    }
    
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);
        
        int uiIdx = GameManager::get().getInventory().indexAtScreenPos(mouseWinPos, window);
        if (uiIdx >= 0) {
            const Item* it = GameManager::get().getInventory().itemAt((unsigned)uiIdx);
            if (it) it->onClick();
            return;
        }
        
        if (!isDebugPlacing) {
            sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mouseWinPos);
            
            std::vector<std::string> currentRoomTriggers;
            if (currentRoom == &rooms["first"]) {
                currentRoomTriggers.push_back("first");
            } else if (currentRoom == &rooms["second"]) {
                currentRoomTriggers.push_back("second_up");
                currentRoomTriggers.push_back("second_right");
                currentRoomTriggers.push_back("second_down");
                currentRoomTriggers.push_back("second_left");
            } else if (currentRoom == &rooms["bathroom"]) {
                currentRoomTriggers.push_back("bathroom");
            } else if (currentRoom == &rooms["patio"]) {
                currentRoomTriggers.push_back("patio");
            } else if (currentRoom == &rooms["garage"]) {
                currentRoomTriggers.push_back("garage");
            }
            
            for (const auto& triggerName : currentRoomTriggers) {
                if (doorTriggers.count(triggerName) && doorTriggers[triggerName].contains(mouseWorldPos)) {
                    Vec2f targetPos(mouseWorldPos.x, mouseWorldPos.y);
                    Room* nextRoomPtr = nullptr;

                    if (triggerName == "first") nextRoomPtr = &rooms["second"];
                    else if (triggerName == "second_up") nextRoomPtr = &rooms["first"];
                    else if (triggerName == "second_right") nextRoomPtr = &rooms["bathroom"];
                    else if (triggerName == "second_down") nextRoomPtr = &rooms["patio"];
                    else if (triggerName == "second_left") nextRoomPtr = &rooms["garage"];
                    else if (triggerName == "bathroom") nextRoomPtr = &rooms["second"];
                    else if (triggerName == "patio") nextRoomPtr = &rooms["second"];
                    else if (triggerName == "garage") nextRoomPtr = &rooms["second"];

                    if (nextRoomPtr) {
                        auto& navGrid = currentRoom->getNavGrid();
                        Point start = navGrid.worldToGrid(GameManager::get().getPlayer().getPosition());
                        Point end = navGrid.worldToGrid(targetPos);
                        
                        if (navGrid.isWalkable(end)) {
                            std::vector<Point> path = pathfinder.findPath(navGrid, start, end);
                            if (!path.empty()) {
                                GameManager::get().getPlayer().setPath(path, navGrid);
                                m_pendingRoomSwitch = true;
                                m_pendingNextRoom = nextRoomPtr;
                                std::cout << "Walking to door (" << triggerName << ")..." << std::endl;
                            }
                        }
                        return;
                    }
                }
            }

            m_pendingRoomSwitch = false;
            m_pendingNextRoom = nullptr;
            if (currentRoom) currentRoom->handleEvent(event, window);
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
        sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);
        int uiIdx = GameManager::get().getInventory().indexAtScreenPos(mouseWinPos, window);
        if (uiIdx >= 0) {
            draggingItem = GameManager::get().getInventory().pickAt(uiIdx);
            if (draggingItem) draggingFrom = uiIdx;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right && draggingItem) {
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

void Past0::update(sf::Time dt)
{
    currentRoom->update(dt);
    GameManager::get().getPlayer().update(dt);

    if (m_pendingRoomSwitch && !GameManager::get().getPlayer().isMoving()) {
        if (m_pendingNextRoom) {
            m_previousRoom = currentRoom;
            currentRoom = m_pendingNextRoom;
            
            if (currentRoom == &rooms["first"]) {
                GameManager::get().getPlayer().setPosition(542.f, 446.f);
            } else if (currentRoom == &rooms["second"]) {
                if (m_previousRoom == &rooms["first"]) {
                    GameManager::get().getPlayer().setPosition(398.f, 200.f);
                } else if (m_previousRoom == &rooms["bathroom"]) {
                    GameManager::get().getPlayer().setPosition(680.f, 400.f);
                } else if (m_previousRoom == &rooms["patio"]) {
                    GameManager::get().getPlayer().setPosition(400.f, 520.f);
                } else if (m_previousRoom == &rooms["garage"]) {
                    GameManager::get().getPlayer().setPosition(120.f, 300.f);
                }
            } else if (currentRoom == &rooms["bathroom"]) {
                GameManager::get().getPlayer().setPosition(100.f, 450.f);
            } else if (currentRoom == &rooms["patio"]) {
                GameManager::get().getPlayer().setPosition(570.f, 140.f);
            } else if (currentRoom == &rooms["garage"]) {
                GameManager::get().getPlayer().setPosition(700.f, 300.f);
            }
            
            std::cout << "Switched room!" << std::endl;
        }
        m_pendingRoomSwitch = false;
        m_pendingNextRoom = nullptr;
    }
}

void Past0::render(sf::RenderWindow& window)
{
    currentRoom->render(window);
    
    // ============================================================
    // SISTEMA DE DEBUG: Mover sprite con el mouse
    // ============================================================
    if (isDebugPlacing && debugSprite != nullptr) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        debugSprite->setPosition(mousePos);
        
        // Mostrar coords en consola
        std::cout << debugSpriteName << "->sprite.setPosition(" 
                  << mousePos.x << ", " << mousePos.y << ");" << std::endl;
    }
    
    // DEBUG: Visualizar triggers de puertas
    if (isDebugPlacing) {
        std::vector<std::string> currentRoomTriggers;
        
        if (currentRoom == &rooms["first"]) {
            currentRoomTriggers.push_back("first");
        } else if (currentRoom == &rooms["second"]) {
            currentRoomTriggers.push_back("second_up");
            currentRoomTriggers.push_back("second_right");
            currentRoomTriggers.push_back("second_down");
            currentRoomTriggers.push_back("second_left");
        } else if (currentRoom == &rooms["bathroom"]) {
            currentRoomTriggers.push_back("bathroom");
        } else if (currentRoom == &rooms["patio"]) {
            currentRoomTriggers.push_back("patio");
        } else if (currentRoom == &rooms["garage"]) {
            currentRoomTriggers.push_back("garage");
        }
        
        for (const auto& triggerName : currentRoomTriggers) {
            if (doorTriggers.count(triggerName)) {
                sf::RectangleShape debugRect;
                debugRect.setPosition(doorTriggers[triggerName].left, doorTriggers[triggerName].top);
                debugRect.setSize(sf::Vector2f(doorTriggers[triggerName].width, doorTriggers[triggerName].height));
                debugRect.setFillColor(sf::Color(255, 0, 0, 80));
                debugRect.setOutlineColor(sf::Color::Red);
                debugRect.setOutlineThickness(2.f);
                window.draw(debugRect);
            }
        }
    }
    
    auto prevView = window.getView();
    window.setView(window.getDefaultView());
    sf::Vector2u ws = window.getSize();
    float margin = 8.f;
    GameManager::get().getInventory().setBasePosition({ margin, float(ws.y) - margin - float(GameManager::get().getInventory().displaySlotHeight()) });
    GameManager::get().getInventory().draw(window);

    if (draggingItem) {
        sf::Vector2i mp = sf::Mouse::getPosition(window);
        sf::Sprite s = draggingItem->sprite();
        sf::FloatRect gb = s.getGlobalBounds();
        s.setPosition(float(mp.x) - gb.width/2.f, float(mp.y) - gb.height/2.f);
        window.draw(s);
    }

    window.setView(prevView);
}