#include "Pasts/PastA.hpp"
#include <iostream>
#include "Scenes/loco1.hpp"
#include <SFML/System/Time.hpp>
#include "../Include/Utils/DialogueSequence.hpp"


void PastA::init()
{
    // ============================================================
    // Carga de Diálogos
    // ============================================================
    dialogueUI.setGame(this->game);
    dialogueStack = std::make_unique<DialogueStack>(*game);

    loadDialogs();

    // ============================================================
    // HABITACIÓN 1: CUARTO (Bedroom)
    // ============================================================
    auto& cuartoRoom = rooms["cuarto"] = Room();
    cuartoRoom.setBackground("assets/textures/PastA/cuarto.png");
    cuartoRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    cuartoRoom.getBackground().sprite.setPosition(0, 0);
    cuartoRoom.setCollisionAndGrid("assets/textures/PastA/Colisiones/cuarto_colision.png");
    cuartoRoom.setGame(this->game);

    cuartoRoom.addObject("sillon", "assets/textures/PastA/sillon.png", 633, 240, 0);
    cuartoRoom.addObject("silla", "assets/textures/PastA/silla.png", 247, 283, 0, 0.7);
    cuartoRoom.addObject("mesa", "assets/textures/PastA/mesa.png", 483, 304, 0);
    

    // ============================================================
    // HABITACIÓN 2: pasillo (Lab)
    // ============================================================
    auto& pasilloRoom = rooms["pasillo"] = Room();
    pasilloRoom.setBackground("assets/textures/PastA/pasillo.png");
    pasilloRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    pasilloRoom.getBackground().sprite.setPosition(0, 0);
    pasilloRoom.setCollisionAndGrid("assets/textures/PastA/Colisiones/pasillo_colision.png");
    pasilloRoom.setGame(this->game);

    pasilloRoom.addObject("agua", "assets/textures/PastA/agua.png", 719, 416);
    pasilloRoom.addObject("escritorio", "assets/textures/PastA/escritorio.png", 16, 291);
    pasilloRoom.addObject("carrito", "assets/textures/PastA/carrito.png", 192, 361);


    doorTriggers["pasillo"] = sf::FloatRect(305.f, 518.f, 150.f, 120.f);
    doorTriggers["cuarto"] = sf::FloatRect(358.f, 93.f, 80.f, 120.f);
   
    currentRoom = &rooms["cuarto"];
    
    NPC doctor;
    doctor.init("assets/textures/PastA/doctor_spritesheet.png", Vec2f(250.f, 400.f), true);
    doctor.getSprite().setPosition(250.f, 400.f); // <--- Coordenadas del salón
    pasilloRoom.addNpc("doctor", doctor);

    rooms["pasillo"].getNpc("doctor").getSprite().setScale(1.0f, 1.0f);
    pasilloRoom.setInteractionToNpc("doctor", [this](){
        showDialogue = true;
    });

    auto& GM = GameManager::get();
    GM.getPlayer().setPosition(400.f, 300.f);
    GM.getPlayer().getSprite().setScale(2.0f, 2.0f);
}

void PastA::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    //GameUtils::testSpritePosition(rooms["pasillo"].getEntity("carrito").sprite, window);
    auto& GM = GameManager::get();
    sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);

    //Click izquierdo
    
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);
        
        int uiIdx = GM.getInventory().indexAtScreenPos(mouseWinPos, window);
        if (uiIdx >= 0) {
            const Item* it = GM.getInventory().itemAt((unsigned)uiIdx);
            if (it) it->onClick();
            return;
        }
        
        if (currentRoom == &rooms["pasillo"]) {
            NPC& doctor = currentRoom->getNpc("doctor");
            if (doctor.getSprite().getGlobalBounds().contains(clickPos)) {
                doctor.interact();
            }

            for(auto& pair : rooms["pasillo"].getEntities()){
                Entity& entity = *pair.second;
                if(entity.sprite.getGlobalBounds().contains(clickPos) && currentRoom == &rooms["pasillo"]) {
                    entity.interact();
                    break;
                }
            }
        }

        if (!showDialogue) {
            sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mouseWinPos);
            
            std::vector<std::string> currentRoomTriggers;
            if (currentRoom == &rooms["cuarto"]) {
                currentRoomTriggers.push_back("cuarto");
            } else if (currentRoom == &rooms["pasillo"]) {
                currentRoomTriggers.push_back("pasillo");
            }
            
            for (const auto& triggerName : currentRoomTriggers) {
                if (doorTriggers.count(triggerName) && doorTriggers[triggerName].contains(mouseWorldPos)) {
                    Vec2f targetPos(mouseWorldPos.x, mouseWorldPos.y);
                    Room* nextRoomPtr = nullptr;

                    if (triggerName == "cuarto") nextRoomPtr = &rooms["pasillo"];
                    else if (triggerName == "pasillo") nextRoomPtr = &rooms["cuarto"];

                    if (nextRoomPtr) {
                        auto& navGrid = currentRoom->getNavGrid();
                        Point start = navGrid.worldToGrid(GM.getPlayer().getPosition());
                        Point end = navGrid.worldToGrid(targetPos);
                        
                        if (navGrid.isWalkable(end)) {
                            std::vector<Point> path = pathfinder.findPath(navGrid, start, end);
                            if (!path.empty()) {
                                GM.getPlayer().setPath(path, navGrid);
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
        int uiIdx = GM.getInventory().indexAtScreenPos(mouseWinPos, window);
        if (uiIdx >= 0) {
            draggingItem = GM.getInventory().pickAt(uiIdx);
            if (draggingItem) draggingFrom = uiIdx;
        }
    }
    // Eventos de presionar botón izquierdo
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (showDialogue) return;
        sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);

        /*if (rooms["pasillo"].getEntity("mesa").sprite.getGlobalBounds().contains(clickPos) && currentRoom == &rooms["pasillo"]) {
                std::cout << "Clic en la mesa!" << std::endl;
                // Tocar la mesa desencadena el evento de un cuadro de diálogo
                showDialogue = true;
        } */
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right && draggingItem) {
        sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);
        int idx = GM.getInventory().indexAtScreenPos(mouseWinPos, window);
        if (idx >= 0) {
            GM.getInventory().insertAt(idx, *draggingItem);
        } else {
            GM.getInventory().insertAt(draggingFrom >= 0 ? (unsigned)draggingFrom : GM.getInventory().size(), *draggingItem);
        }
        draggingItem.reset();
        draggingFrom = -1;
    }
    
    // Evento al clickar continuar en el diálogo
    if (dialogueUI.wasAdvanceClicked()) {
        if (dialogueStack->isStackEmpty()) {
            showDialogue = false;
            return;
        }
        const DialogueSequence& currentDialogue = dialogueStack->getCurrentDialogue();
        
        if (currentDialogue.getType() == DialogueType::CHOICE) {
            // Obtener la opción elegida
            int chosenIndex = dialogueUI.getChosenOption();
            if (chosenIndex >= 0) {
                std::string nextSceneID = dialogueStack->chooseOption(chosenIndex);
                std::cout << "Opción elegida: " << chosenIndex << ", nextScene: " << nextSceneID << std::endl;
                //CAMBIAR ESTO
                this->game->changeState(new loco1());
                if (dialogueStack->isStackEmpty()) {
                    showDialogue = false;
                }
            }
            return;
        }
        // Si es diálogo normal, avanza la línea
        dialogueStack->advanceLine();

        if (dialogueStack->isStackEmpty()) {
            showDialogue = false;
        }

        if (dialogueUI.wasAdvanceClicked()) {
        if (dialogueStack->isStackEmpty()) {
            this->game->changeState(new loco1());
            return;
        }
        const DialogueSequence& currentDialogue = dialogueStack->getCurrentDialogue();
       
        if (currentDialogue.getLines()[0].getPortraitID() == "Last_line") {
            // Obtener la opción elegida
                this->game->changeState(new loco1());
            }
            return;
        }
        // Si es diálogo normal, avanza la línea
        dialogueStack->advanceLine();
    }
}

void PastA::update(sf::Time dt)
{
    currentRoom->update(dt);
    GameManager::get().getPlayer().update(dt);
    //m_npcAnimationTimer += dt;
    
    /*if(currentRoom == &rooms["yard"]) {
        
        if (m_npcAnimationTimer.aspasillos() > 6.0f)
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
    }*/

    
    
    if (m_pendingRoomSwitch && !GameManager::get().getPlayer().isMoving()) {
        if (m_pendingNextRoom) {
            m_previousRoom = currentRoom;
            currentRoom = m_pendingNextRoom;
            
            if (currentRoom == &rooms["cuarto"]) {
                GameManager::get().getPlayer().setPosition(400.f, 560.f);
            } else if (currentRoom == &rooms["pasillo"]) {
                if (m_previousRoom == &rooms["cuarto"]) {
                    GameManager::get().getPlayer().setPosition(400.f, 580.f);
                } 
            }
        }
        m_pendingRoomSwitch = false;
        m_pendingNextRoom = nullptr;
    }
}

void PastA::render(sf::RenderWindow& window)
{
    window.clear();

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
}

void PastA::loadDialogs() {
    // 💡 Paso 1: Crea y puebla los DialogueLine.
    DialogueLine line1("Doctor", "¡Oh! Hola John, veo que despertaste... ¿Cómo te sientes?", "Pause");
    DialogueLine line2("John Barr", "Confundido... ¿Por qué estoy aquí? ¿Y mi esposa?", "Niña_01");
    DialogueLine line3("Doctor", "Claro, tu esposa... ¿Quieres?... ¿Saber que pasó con ella?.", "Main_Character");
    
    // --- Secuencia 1: Diálogo Normal (tipo MONOLOGUE o NORMAL)
    DialogueSequence introDialogue(DialogueType::NORMAL);
    introDialogue.dialogueLines.emplace_back(line1);
    introDialogue.dialogueLines.emplace_back(line2);
    introDialogue.dialogueLines.emplace_back(line3);
    
    // --- Secuencia 2: Diálogo de Opción (tipo CHOICE)
    DialogueSequence choiceDialogue(DialogueType::CHOICE);
    
    // Inicialización explícita para garantizar que el texto de la pregunta no esté vacío.
    DialogueLine questionLine("Narrador", "¿A dónde irás?", "id_retrato_heroe"); 
    choiceDialogue.dialogueLines.push_back(questionLine);
}