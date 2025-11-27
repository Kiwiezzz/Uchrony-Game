#include "Pasts/Past0.hpp"
#include "Pasts/PastB.hpp"
#include "Pasts/PastA.hpp"
#include "Core/Game.hpp"
#include <iostream>
#include <SFML/System/Time.hpp>
#include "../Include/Utils/DialogueSequence.hpp"


/// @brief Si logra encontrar camino para aproximarse retorna true
bool Past0::approachEntity(const NavGrid& navGrid, Vec2f targetPos, float stopDistance)
{
    Vec2f playerPos = GameManager::get().getPlayer().getPosition(); // Singleton, todo bien
    
    // Calcular punto destino (80px cerca)
    Vec2f dirToPlayer = (playerPos - targetPos).normalized();
    targetPos = targetPos + dirToPlayer * stopDistance;
    
    Point start = navGrid.worldToGrid(playerPos);
    Point end = navGrid.worldToGrid(targetPos);
    
    if (navGrid.isWalkable(end)) {
        std::vector<Point> path = GameManager::get().pathfinder.findPath(navGrid, start, end);
        
        if (!path.empty()) {
            GameManager::get().getPlayer().setPath(path, navGrid);

            return true;
        }
    }

    return false;
}


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
    // Carga de Diálogos
    // ============================================================
    dialogueUI.setGame(this->game);
    dialogueStack = std::make_unique<DialogueStack>(*game);
    dialogueStack_npc = std::make_unique<DialogueStack>(*game);
    dialogueStack_machine = std::make_unique<DialogueStack>(*game);
    showDialogue = true;

    loadDialogs();

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

    firstRoom.addObject("marco_puerta", "assets/textures/Past0/marco_puerta.png", 333, 412, 1);
    firstRoom.addObject("planta", "assets/textures/Past0/planta.png", 42, 418);
    firstRoom.addObject("mesa_cuarto", "assets/textures/Past0/mesa_cuarto.png", 621, 283);
    firstRoom.addObject("sillita", "assets/textures/Past0/sillita.png", 552, 299);

    if(!GameManager::get().getInventory().hasItem(1))
    {
        auto red_key = std::make_unique<ObjectRoom>("assets/textures/Past0/llave_roja.png");
        red_key->sprite.setPosition(152, 189);
        red_key->sprite.setScale(0.05f, 0.05f);
        red_key->setlayer(1);  // Layer 1 = delante del jugador
        firstRoom.addEntity("red_key", std::move(red_key));
        firstRoom.setInteractionToEntity("red_key", 
            [this]()
            {
                std::cout << "Interaccion con llave roja" << std::endl;
                items["red_key"] = TextureAsset("assets/textures/Past0/llave_roja.png");
                Item red_keyItem(1, items["red_key"].texture);
                bool added = GameManager::get().getInventory().add(red_keyItem);

                rooms["first"].removeEntity("red_key");
                
            }
        );
    }
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
    auto mesa = std::make_unique<ObjectRoom>("assets/textures/mesa.png");
    mesa->sprite.setPosition(397, 494);
    mesa->sprite.setOrigin(float(mesa->texture.getSize().x) / 2.f, float(mesa->texture.getSize().y));
    mesa->setlayer(0);  // Layer 0 = detrás del jugador
    secondRoom.addEntity("mesa", std::move(mesa));
    secondRoom.setInteractionToEntity("mesa", 
        [this]()
        {
            std::cout << "Hola, hiciste click en la mesa, sí sirve" << std::endl;
            //showDialogue = true;
        }
    );

    if(!GameManager::get().getInventory().hasItem(3))
    {
        auto ocarina = std::make_unique<ObjectRoom>("assets/textures/Ocarina.png");
        ocarina->sprite.setPosition(397, 380);
        ocarina->sprite.setScale(0.05f, 0.05f);
        ocarina->setlayer(0);  // Layer 0 = detrás del jugador
        secondRoom.addEntity("ocarina", std::move(ocarina));
        secondRoom.setInteractionToEntity("ocarina", 
            [this]()
        {
            items["ocarina"] = TextureAsset("assets/textures/Ocarina.png");
            Item ocarinaItem(3, items["ocarina"].texture);
            bool added = GameManager::get().getInventory().add(ocarinaItem);

            rooms["second"].removeEntity("ocarina");
        }
    );
    }
    
    auto mesa2 = std::make_unique<ObjectRoom>("assets/textures/mesa_2.png");
    mesa2->sprite.setPosition(667, 326);
    mesa2->sprite.setOrigin(float(mesa2->texture.getSize().x) / 2.f, float(mesa2->texture.getSize().y));
    mesa2->setlayer(0);
    secondRoom.addEntity("mesa2", std::move(mesa2));
    
    auto botella = std::make_unique<ObjectRoom>("assets/textures/Past0/botella.png");
    botella->sprite.setPosition(597, 185);
    botella->setlayer(1);  // Layer 1 = delante del jugador
    secondRoom.addEntity("botella", std::move(botella));
    secondRoom.setInteractionToEntity("botella", 
        [this]()
        {
            std::cout << "a" << std::endl;
        }
    );
    
    // ============================================================
    // HABITACIÓN 3: BAÑO (Bathroom)
    // ============================================================
    auto& bathroomRoom = rooms["bathroom"] = Room();
    bathroomRoom.setBackground("assets/textures/Past0/bath.png");
    bathroomRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    bathroomRoom.getBackground().sprite.setPosition(0, 0);
    bathroomRoom.setCollisionAndGrid("assets/textures/Past0/Colisiones/bath_colision.png");
    bathroomRoom.setGame(this->game);

    auto bathtub = std::make_unique<ObjectRoom>("assets/textures/Past0/bathtub.png");
    bathtub->sprite.setPosition(0, 391);
    bathtub->setlayer(1);  // Layer 1 = delante del jugador
    bathroomRoom.addEntity("bathtub", std::move(bathtub));

    auto plant = std::make_unique<ObjectRoom>("assets/textures/Past0/Plant.png");
    plant->sprite.setPosition(703, 386);
    plant->setlayer(1);  // Layer 1 = delante del jugador
    bathroomRoom.addEntity("plant", std::move(plant));

// ============================================================
    // HABITACIÓN 4: PATIO (Yard)
    // ============================================================
    auto& yardRoom = rooms["yard"] = Room();
    yardRoom.setBackground("assets/textures/Past0/yard.png");
    yardRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    yardRoom.getBackground().sprite.setPosition(0, 0);
    yardRoom.setCollisionAndGrid("assets/textures/Past0/Colisiones/yard_colision.png");
    yardRoom.setGame(this->game);

    if(!GameManager::get().getInventory().hasItem(2))
    {
        auto blue_key = std::make_unique<ObjectRoom>("assets/textures/Past0/llave_azul.png");
        blue_key->sprite.setPosition(152, 500);
        blue_key->sprite.setScale(0.05f, 0.05f);
        blue_key->setlayer(1);  // Layer 1 = delante del jugador
        yardRoom.addEntity("blue_key", std::move(blue_key));
        yardRoom.setInteractionToEntity("blue_key", 
            [this]()
            {
                std::cout << "Interaccion con llave azul" << std::endl;
            items["blue_key"] = TextureAsset("assets/textures/Past0/llave_azul.png");
                Item blue_keyItem(2, items["blue_key"].texture);
                bool added = GameManager::get().getInventory().add(blue_keyItem);

                rooms["yard"].removeEntity("blue_key");
                
            }
        );
    }
    NPC neighbor_npc;
    neighbor_npc.init("assets/textures/Past0/neighbor_npc.png", Vec2f(520.f, 250.f), true);
    
    yardRoom.addNpc("neighbor", neighbor_npc);

    rooms["yard"].getNpc("neighbor").setInteraction([this]() 
    {
        // Al capturar [this], podemos acceder a 'rooms' directamente
        auto& neighbor_npc = rooms["yard"].getNpc("neighbor");
        
        std::cout << "Clic en Neighbor!" << std::endl;
        
        // 1. Detener al NPC
        neighbor_npc.stopMovement();

        // 2. Mover al jugador cerca del NPC
        // Accedemos a 'currentRoom' directamente gracias a [this]
        auto& navGrid = currentRoom->getNavGrid(); 
        
        Vec2f targetPos = neighbor_npc.getPosition();

        m_approachingEntity = approachEntity(navGrid, targetPos, 80.f);
    });
    
    rooms["yard"].getNpc("neighbor").getSprite().setPosition(520.f, 250.f);
    rooms["yard"].getNpc("neighbor").getSprite().setScale(2.0f, 2.0f);
    rooms["yard"].getNpc("neighbor").addAnimation("Posicion_Espalda", 0, 1, 3.0f, false, 2);
    rooms["yard"].getNpc("neighbor").addAnimation("Posicion_Espalda2", 0, 1, 3.0f, false, 5);
    rooms["yard"].getNpc("neighbor").addAnimation("Posicion_Pectorales", 2, 1, 3.0f, false, 6);
    rooms["yard"].getNpc("neighbor").addAnimation("Posicion_Contento", 3, 1, 5.0f, false, 2);
                            //row(r), frameCount(fc), duration(d), loop(l), startColumn(sc)

    // ============================================================
    // HABITACIÓN 5: GARAGE
    // ============================================================
    auto& garageRoom = rooms["garage"] = Room();
    garageRoom.setBackground("assets/textures/Past0/garage.png");
    garageRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    garageRoom.getBackground().sprite.setPosition(0, 0);
    garageRoom.setCollisionAndGrid("assets/textures/Past0/Colisiones/garage_colision.png");
    garageRoom.setGame(this->game);

    auto capo = std::make_unique<ObjectRoom>("assets/textures/Past0/Capo.png");
    capo->sprite.setPosition(273, 204);
    capo->setlayer(1);  // Layer 1 = delante del jugador
    garageRoom.addEntity("capo", std::move(capo));

    auto esquina = std::make_unique<ObjectRoom>("assets/textures/Past0/Esquina1.png");
    esquina->sprite.setPosition(26, 254);
    esquina->setlayer(1);  // Layer 1 = delante del jugador
    garageRoom.addEntity("esquina", std::move(esquina));

    auto esquina2 = std::make_unique<ObjectRoom>("assets/textures/Past0/Esquina2.png");
    esquina2->sprite.setPosition(628, 261);
    esquina2->setlayer(1);  // Layer 1 = delante del jugador
    garageRoom.addEntity("esquina2", std::move(esquina2));

    auto machine = std::make_unique<ObjectRoom>("assets/textures/Past0/maquina_del_tiempo.png");
    machine->sprite.setPosition(379, 450);
    machine->sprite.setScale(0.13f, 0.13f);
    machine->sprite.setOrigin(machine->texture.getSize().x / 2.f, machine->texture.getSize().y / 2.f);
    garageRoom.addEntity("machine", std::move(machine));

    rooms["garage"].getEntity("machine").setInteraction([this]()
    {
        std::cout << "Hola, hiciste click en la maquina, sí sirve" << std::endl;
        auto& machine = rooms["garage"].getEntity("machine");
        auto& navGrid = currentRoom->getNavGrid(); 
        
        Vec2f targetPos = GameUtils::toVec2f(machine.sprite.getPosition());

         // Intentar acercarse
        if (approachEntity(navGrid, targetPos, 100.f)) {
            m_approachingMachine = true;
            // El diálogo se cargará en update() cuando termine de caminar
        } else {
            // Si no puede caminar (muy cerca o bloqueado), mostrar diálogo directo
            std::cout << "No se pudo encontrar camino, mostrando diálogo directo." << std::endl;
            loadMachineDialogs();
            showMachineDialogue = true;
        }
    });

    // ============================================================
    // CONFIGURACIÓN DE TRIGGERS DE PUERTAS
    // ============================================================
    doorTriggers["first"] = sf::FloatRect(305.f, 518.f, 150.f, 120.f);
    doorTriggers["second_up"] = sf::FloatRect(358.f, 93.f, 80.f, 120.f);
    doorTriggers["second_right"] = sf::FloatRect(720.f, 250.f, 80.f, 600.f);
    doorTriggers["second_down"] = sf::FloatRect(230.f, 520.f, 400.f, 80.f);
    doorTriggers["second_left"] = sf::FloatRect(0.f, 250.f, 80.f, 600.f);
    doorTriggers["bathroom"] = sf::FloatRect(0.f, 250.f, 100.f, 300.f);
    doorTriggers["yard"] = sf::FloatRect(520.f, 100.f, 100.f, 110.f);
    doorTriggers["garage"] = sf::FloatRect(720.f, 250.f, 80.f, 80.f);
   
    currentRoom = &rooms["first"];
    
    auto& GM = GameManager::get();
    GM.getPlayer().setPosition(400.f, 300.f);
    GM.getPlayer().getSprite().setScale(2.0f, 2.0f);


    if (!ocarinaBuffer.loadFromFile("assets/sounds/ocarina.mp3")) {
        std::cerr << "Warning: no se cargo assets/sounds/ocarina.mp3" << std::endl;
    }
    
    ocarinaSound.setBuffer(ocarinaBuffer);
}

void Past0::handleEvent(sf::Event& event, sf::RenderWindow& window)
{

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);
        
        int uiIdx = GameManager::get().getInventory().indexAtScreenPos(mouseWinPos, window);
        if (uiIdx >= 0) {
            const Item* it = GameManager::get().getInventory().itemAt((unsigned)uiIdx);
            if (it) {
                it->onClick();
        
                if (it->id() == 3) {
                    ocarinaSound.stop();
                    ocarinaSound.play();
                }
            }
            return;
        }
        
        
        if (!showDialogue) {
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
            } else if (currentRoom == &rooms["yard"]) {
                currentRoomTriggers.push_back("yard");
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
                    else if (triggerName == "second_down") nextRoomPtr = &rooms["yard"];
                    else if (triggerName == "second_left") nextRoomPtr = &rooms["garage"];
                    else if (triggerName == "bathroom") nextRoomPtr = &rooms["second"];
                    else if (triggerName == "yard") nextRoomPtr = &rooms["second"];
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
    // Eventos de presionar botón izquierdo
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (showDialogue) return;
        sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);


        if(currentRoom == &rooms["first"]){
            for(auto& pair : rooms["first"].getEntities()){
                Entity& entity = *pair.second;
                if(entity.sprite.getGlobalBounds().contains(clickPos) && currentRoom == &rooms["first"]) {
                    entity.interact();
                    break;
                }
            }
        }
        /// Aquí todas las interacciones de second
        for(auto& pair : rooms["second"].getEntities()){
            Entity& entity = *pair.second;
            if(entity.sprite.getGlobalBounds().contains(clickPos) && currentRoom == &rooms["second"]) {
                entity.interact();
                break;
            }
        } 

        for(auto& pair : rooms["garage"].getEntities()){
            //PAIR SECOND
            Entity& entity = *pair.second;
            if(entity.sprite.getGlobalBounds().contains(clickPos) && currentRoom == &rooms["garage"]) {
                entity.interact();
                break;
            }
        } 

        // Interacción con NPC Neighbor en Yard
        if (currentRoom == &rooms["yard"]) {
            NPC& neighbor = currentRoom->getNpc("neighbor");
            if (neighbor.getSprite().getGlobalBounds().contains(clickPos)) {
                neighbor.interact();
                
            }
            for(auto& pair : rooms["yard"].getEntities()){
                Entity& entity = *pair.second;
                if(entity.sprite.getGlobalBounds().contains(clickPos) && currentRoom == &rooms["yard"]) {
                    entity.interact();
                    break;
                }
            }
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
    
    // Evento al clickar continuar en el diálogo
    if (dialogueUI.wasAdvanceClicked()) {
        
        // 1. Diálogo General (Narrador / Intro)
        if (showDialogue) {
            if (dialogueStack->isStackEmpty()) {
                showDialogue = false;
                return;
            }
            // Avance normal para el diálogo general
            dialogueStack->advanceLine();

            if (dialogueStack->isStackEmpty()) {
                showDialogue = false;
            }
        } 
        // 2. Diálogo del Vecino
        else if (showNeighborDialogue) {
             if (dialogueStack_npc->isStackEmpty()) {
                showNeighborDialogue = false;
                if (currentRoom == &rooms["yard"]) {
                    currentRoom->getNpc("neighbor").setWalkable(true);
                }
                return;
            }
            
            dialogueStack_npc->advanceLine();

            if (dialogueStack_npc->isStackEmpty()) {
                showNeighborDialogue = false;
                if (currentRoom == &rooms["yard"]) {
                    currentRoom->getNpc("neighbor").setWalkable(true);
                }
            }
        }
        // 3. Diálogo de la Máquina (Aquí va la lógica de elección)
        else if (showMachineDialogue) {
            if (dialogueStack_machine->isStackEmpty()) {
                showMachineDialogue = false;
                return;
            }
            const DialogueSequence& currentDialogue = dialogueStack_machine->getCurrentDialogue();
            
            // Lógica de elección específica para la máquina
            if (currentDialogue.getType() == DialogueType::CHOICE) {
                int chosenIndex = dialogueUI.getChosenOption();
                if (chosenIndex >= 0) {
                    // Usamos dialogueStack_machine aquí, que es el correcto
                    std::string nextSceneID = dialogueStack_machine->chooseOption(chosenIndex);
                    std::cout << "Opción elegida Maquina: " << chosenIndex << ", nextScene: " << nextSceneID << std::endl;
                    
                    if (nextSceneID == "past_a_id") {
                        this->game->changeState(new PastA()); 
                        std::cout << ">>> Viajando al Pasado A..." << std::endl;
                    } else if (nextSceneID == "past_b_id") {
                        this->game->changeState(new PastB()); 
                        std::cout << ">>> Viajando al Pasado B..." << std::endl;
                    }

                    if (dialogueStack_machine->isStackEmpty()) {
                        showMachineDialogue = false;
                    }
                }
                return; // Importante retornar para no avanzar línea inmediatamente
            }

            // Si es diálogo normal, avanza la línea
            dialogueStack_machine->advanceLine();

            if (dialogueStack_machine->isStackEmpty()) {
                showMachineDialogue = false;
            }
        }
    }
}

void Past0::update(sf::Time dt)
{
    currentRoom->update(dt);
    GameManager::get().getPlayer().update(dt);
    m_npcAnimationTimer += dt;
    
    if(currentRoom == &rooms["yard"]) {
        
        if (m_npcAnimationTimer.asSeconds() > 6.0f)
        {
            m_npcAnimationTimer = sf::Time::Zero; 
            int random = rand() % 100;

            if (random < 20) {
                currentRoom->getNpc("neighbor").playAction("Posicion_Espalda", 2.f);
            } else if (random >= 20 && random < 30) {
                currentRoom->getNpc("neighbor").playAction("Posicion_Espalda2", 2.f);
            } else if (random >= 30 && random < 40) {
                currentRoom->getNpc("neighbor").playAction("Posicion_Pectorales", 2.f);
            } else if (random >= 40 && random < 50) {
                currentRoom->getNpc("neighbor").playAction("Posicion_Contento", 2.f);
            }
        }

        currentRoom->getNpc("neighbor").update(dt, currentRoom->getNavGrid());
    }

    // Lógica de acercamiento a la Entidad
    if (m_approachingEntity) {
        auto& player = GameManager::get().getPlayer();
        if (!player.isMoving()) {
            // El jugador ha llegado (o se ha detenido)
            m_approachingEntity = false;
            
            if (currentRoom == &rooms["yard"]) {
                NPC& neighbor = currentRoom->getNpc("neighbor");
                
                // Calcular direcciones para mirarse mutuamente
                Vec2f playerPos = player.getPosition();
                Vec2f targetPos = neighbor.getPosition();
                
                Vec2f dirToNPC = targetPos - playerPos;
                Vec2f dirToPlayer = playerPos - targetPos;
                
                player.faceDirection(dirToNPC);
                neighbor.faceDirection(dirToPlayer);
                
                loadNeighborDialogs();

                showNeighborDialogue = true;
            } else if (currentRoom == &rooms["garage"] && m_approachingMachine) {
                loadMachineDialogs();
                showMachineDialogue = true;
            }
        }
    }
    
    if (m_pendingRoomSwitch && !GameManager::get().getPlayer().isMoving()) {
        if (m_pendingNextRoom) {
            m_previousRoom = currentRoom;
            currentRoom = m_pendingNextRoom;
            
            if (currentRoom == &rooms["first"]) {
                GameManager::get().getPlayer().setPosition(400.f, 560.f);
            } else if (currentRoom == &rooms["second"]) {
                if (m_previousRoom == &rooms["first"]) {
                    GameManager::get().getPlayer().setPosition(398.f, 200.f);
                } else if (m_previousRoom == &rooms["bathroom"]) {
                    GameManager::get().getPlayer().setPosition(680.f, 400.f);
                } else if (m_previousRoom == &rooms["yard"]) {
                    GameManager::get().getPlayer().setPosition(400.f, 520.f);
                } else if (m_previousRoom == &rooms["garage"]) {
                    GameManager::get().getPlayer().setPosition(120.f, 450.f);
                }
            } else if (currentRoom == &rooms["bathroom"]) {
                GameManager::get().getPlayer().setPosition(100.f, 450.f);
            } else if (currentRoom == &rooms["yard"]) {
                GameManager::get().getPlayer().setPosition(570.f, 140.f);
            } else if (currentRoom == &rooms["garage"]) {
                GameManager::get().getPlayer().setPosition(700.f, 300.f);
            }
        }
        m_pendingRoomSwitch = false;
        m_pendingNextRoom = nullptr;
    }
}

void Past0::render(sf::RenderWindow& window)
{
    currentRoom->render(window);
    
    auto prevView = window.getView();
    window.setView(window.getDefaultView());
    sf::Vector2u ws = window.getSize();
    float margin = 8.f;
    GameManager::get().getInventory().setBasePosition({ margin, float(ws.y) - margin - float(GameManager::get().getInventory().displaySlotHeight()) });
    GameManager::get().getInventory().draw(window);

    if (draggingItem) {
        sf::Vector2i mp = sf::Mouse::getPosition(window);
        sf::Sprite s = draggingItem->sprite();
         s.setScale(0.05f, 0.05f);
        sf::FloatRect gb = s.getGlobalBounds();
        s.setPosition(float(mp.x) - gb.width/2.f, float(mp.y) - gb.height/2.f);
        window.draw(s);
    }

    // Restaurar vista previa para dibujar diálogo
    window.setView(prevView);

    if (showDialogue && !dialogueStack->isStackEmpty()) {

        const DialogueSequence& currentDialogue = dialogueStack->getCurrentDialogue(); 
        
        dialogueUI.render(window, currentDialogue, currentDialogue.options, game->getSFMLFont(), dialogueStack->getCurrentLineIndex()); 
    }

    if (showNeighborDialogue && !dialogueStack_npc->isStackEmpty()) {

        const DialogueSequence& currentDialogue = dialogueStack_npc->getCurrentDialogue(); 
        
        dialogueUI.render(window, currentDialogue, currentDialogue.options, game->getSFMLFont(), dialogueStack_npc->getCurrentLineIndex()); 
    }

    if (showMachineDialogue && !dialogueStack_machine->isStackEmpty()) {

        const DialogueSequence& currentDialogue = dialogueStack_machine->getCurrentDialogue(); 
        
        dialogueUI.render(window, currentDialogue, currentDialogue.options, game->getSFMLFont(), dialogueStack_machine->getCurrentLineIndex()); 
    }
}

void Past0::loadDialogs() {
    // 💡 Paso 1: Crea y puebla los DialogueLine.
    DialogueLine line1("Narrador", "Bienvenido a Uchrony Game! Esta es la primera parte del juego.", "237273");
    DialogueLine line2("Narrador", "Mi querido John Barr, creo que te encuentras algo perdido.", "6969");
    DialogueLine line3("John Barr", "Eh? Qué? Dónde estoy?", "237273");
    DialogueLine line4("Narrador", "Tendrás que averiguarlo por tí mismo...", "6969");
    
    // --- Secuencia 1: Diálogo Normal (tipo MONOLOGUE o NORMAL)
    DialogueSequence introDialogue(DialogueType::NORMAL);
    introDialogue.dialogueLines.emplace_back(line1);
    introDialogue.dialogueLines.emplace_back(line2);
    introDialogue.dialogueLines.emplace_back(line3);
    introDialogue.dialogueLines.emplace_back(line4);
    
    /*// --- Secuencia 2: Diálogo de Opción (tipo CHOICE)
    DialogueSequence choiceDialogue(DialogueType::CHOICE);
    
    // Inicialización explícita para garantizar que el texto de la pregunta no esté vacío.
    DialogueLine questionLine("Narrador", "¿A dónde irás?", "id_retrato_heroe"); 
    choiceDialogue.dialogueLines.push_back(questionLine);
    
    // Define las opciones de la elección (este formato push_back está bien)
    choiceDialogue.options.push_back({"Ir al bosque", "scene_forest_id"}); 
    choiceDialogue.options.push_back({"Entrar a la tienda", "scene_shop_id"});
    
    // --- Secuencia 3: Diálogo después de la elección
    DialogueSequence afterChoiceDialogue(DialogueType::NORMAL);
    DialogueLine line5("Narrador", "Excelente elección. Tu aventura continúa...", "id_narrador");
    DialogueLine line6("John Barr", "Espero que sea una buena idea.", "id_john");
    afterChoiceDialogue.dialogueLines.push_back(line5);
    afterChoiceDialogue.dialogueLines.push_back(line6);
    
    // 💡 Paso 3: Empuja las secuencias. (Orden de ejecución: introDialogue -> choiceDialogue -> afterChoiceDialogue)
    // El último en entrar (introDialogue) será el primero en ejecutarse.
    dialogueStack->pushDialogue(afterChoiceDialogue); // Se ejecuta TERCERO (después de elegir)
    dialogueStack->pushDialogue(choiceDialogue);       // Se ejecuta SEGUNDO*/
    dialogueStack->pushDialogue(introDialogue);        // Se ejecuta PRIMERO
}

void Past0::loadNeighborDialogs() {
    DialogueLine line1("Vecino", "Hola!", "id_vecino");
    DialogueLine line2("Vecino", "Gracias por prestarme tu patio para mis poses de Fisicoculturismo", "id_vecino");
    DialogueLine line3("Vecino", "Ya sabes, en mi casa se burlan de mi", "id_vecino");
    DialogueLine line4("Vecino", "Por cierto, que tal tu esposa, ¿Tenias una, no es asi?", "id_vecino");

    DialogueSequence neighborDialogue(DialogueType::NORMAL);
    neighborDialogue.dialogueLines.emplace_back(line1);
    neighborDialogue.dialogueLines.emplace_back(line2);
    neighborDialogue.dialogueLines.emplace_back(line3);
    neighborDialogue.dialogueLines.emplace_back(line4);

    dialogueStack_npc->pushDialogue(neighborDialogue);
}

void Past0::loadMachineDialogs() {
    bool hasRedKey = false;
    bool hasBlueKey = false;
    
    auto& inventory = GameManager::get().getInventory();
    for (unsigned i = 0; i < inventory.size(); ++i) {
        const Item* item = inventory.itemAt(i);
        if (item) {
            if (item->id() == 1) hasRedKey = true; 
            if (item->id() == 2) hasBlueKey = true; 
        }
    }

    if (!hasRedKey && !hasBlueKey) {

        DialogueSequence noKeyDialogue(DialogueType::NORMAL);
        noKeyDialogue.dialogueLines.emplace_back("Maquina del tiempo", "Necesito una llave para activar esto...", "id_retrato_heroe");
        dialogueStack_machine->pushDialogue(noKeyDialogue);
        return;
    }

    DialogueSequence choiceDialogue(DialogueType::CHOICE);
    
    DialogueLine questionLine("Maquina del tiempo", "¿A dónde irás?", "id_retrato_heroe"); 
    choiceDialogue.dialogueLines.push_back(questionLine);
    
    if (hasBlueKey) {
        choiceDialogue.options.push_back({"Ir al Pasado A", "past_a_id"}); 
    }
    if (hasRedKey) {
        choiceDialogue.options.push_back({"Ir al Pasado B", "past_b_id"});
    }
    
    DialogueSequence afterChoiceDialogue(DialogueType::NORMAL);
    DialogueLine line1("Maquina del tiempo", "Excelente elección. Que tengas buen viaje", "id_narrador");
    DialogueLine line2("John Barr", "Espero que esto sea una buena idea.", "id_john");
    afterChoiceDialogue.dialogueLines.push_back(line1);
    afterChoiceDialogue.dialogueLines.push_back(line2);
    
    dialogueStack_machine->pushDialogue(afterChoiceDialogue); 
    dialogueStack_machine->pushDialogue(choiceDialogue);       
}