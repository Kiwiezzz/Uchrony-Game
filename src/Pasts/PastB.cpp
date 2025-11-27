#include "Pasts/PastB.hpp"
#include <iostream>
#include "../Include/Utils/DialogueSequence.hpp"

/**
 * @brief Inicializa todas las habitaciones (rooms) del PastB
 * 
 * Este método se llama una sola vez al inicio para configurar:
 * - Las 2 habitaciones del juego (salon y parquesito)
 * - Los triggers de puertas que permiten cambiar entre habitaciones
 * - La posición inicial del jugador
 */
void PastB::init()
{
    // ============================================================
    // Carga de Diálogos
    // ============================================================
    dialogueStack = std::make_unique<DialogueStack>(*game);

    loadDialogs();

    // ============================================================
    // HABITACIÓN 1: SALÓN (Classroom)
    // ============================================================
    auto& firstRoom = rooms["first"] = Room();
    firstRoom.setBackground("assets/textures/PastB/salon.png");
    firstRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    firstRoom.getBackground().sprite.setPosition(0, 0);
    // El mapa de colisiones define qué áreas son caminables (blanco) y cuáles no (negro)
    firstRoom.setCollisionAndGrid("assets/textures/PastB/Colisiones/salon_colision.png");
    firstRoom.setGame(this->game);
    
    // --- Objetos decorativos en el salón ---
    auto mesa = std::make_unique<ObjectRoom>("assets/textures/PastB/silla_1.png");
    mesa->sprite.setPosition(397, 494);
    mesa->sprite.setOrigin(float(mesa->texture.getSize().x) / 2.f, float(mesa->texture.getSize().y));
    mesa->setlayer(1);  // Layer 0 = detrás del jugador
    firstRoom.addEntity("mesa", std::move(mesa));

    auto mesa2 = std::make_unique<ObjectRoom>("assets/textures/PastB/mesa_2.png");
    mesa2->sprite.setPosition(667, 326);
    mesa2->sprite.setOrigin(float(mesa2->texture.getSize().x) / 2.f, float(mesa2->texture.getSize().y));
    mesa2->setlayer(1);
    firstRoom.addEntity("mesa2", std::move(mesa2));

    auto mesa3 = std::make_unique<ObjectRoom>("assets/textures/PastB/mesa_3.png");
    mesa3->sprite.setPosition(667, 326);
    mesa3->sprite.setOrigin(float(mesa3->texture.getSize().x) / 2.f, float(mesa3->texture.getSize().y));
    mesa3->setlayer(1);
    firstRoom.addEntity("mesa3", std::move(mesa3));

    auto mesa4 = std::make_unique<ObjectRoom>("assets/textures/PastB/mesa_4.png");
    mesa4->sprite.setPosition(667, 326);
    mesa4->sprite.setOrigin(float(mesa4->texture.getSize().x) / 2.f, float(mesa4->texture.getSize().y));
    mesa4->setlayer(1);
    firstRoom.addEntity("mesa4", std::move(mesa4));

    // ============================================================
    // HABITACIÓN 2: PARQUESITO (Park)
    // ============================================================

    auto& secondRoom = rooms["second"] = Room();
    secondRoom.setBackground("assets/textures/PastB/parquesito.png");
    secondRoom.getBackground().sprite.setScale(1.0f, 1.0f);
    secondRoom.getBackground().sprite.setPosition(0, 0);
    secondRoom.setCollisionAndGrid("assets/textures/PastB/Colisiones/parquesito_colision.png");
    secondRoom.setGame(this->game);
    
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
    // ============================================================

    //debugSprite = &esquina2->sprite;
    //debugSpriteName = "esquina2";

    // ============================================================
    // CONFIGURACIÓN DE TRIGGERS DE PUERTAS
    // ============================================================
    doorTriggers["first"] = sf::FloatRect(546.f, 211.f, 123.f, 62.f);
    doorTriggers["second_up"] = sf::FloatRect(358.f, 93.f, 223.f, 72.f);
    doorTriggers["second_right"] = sf::FloatRect(720.f, 250.f, 80.f, 600.f);
    doorTriggers["second_down"] = sf::FloatRect(230.f, 520.f, 400.f, 80.f);
    doorTriggers["second_left"] = sf::FloatRect(0.f, 250.f, 80.f, 600.f);
   
    currentRoom = &rooms["first"];
    
    auto& GM = GameManager::get();
    GM.getPlayer().setPosition(400.f, 300.f);
    GM.getPlayer().getSprite().setScale(2.0f, 2.0f);

    NPC nina;
    nina.init("assets/textures/PastB/Personajes/nina_spritesheet.png", Vec2f(250.f, 400.f), true);
    nina.getSprite().setPosition(250.f, 400.f); // <--- Coordenadas del salón
    firstRoom.addNpc("nina", nina);

    rooms["first"].getNpc("nina").getSprite().setScale(1.0f, 1.0f);
}

void PastB::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    GameUtils::logPosition(GameUtils::getMouseWorldPosition(window));
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
            }
            
            for (const auto& triggerName : currentRoomTriggers) {
                if (doorTriggers.count(triggerName) && doorTriggers[triggerName].contains(mouseWorldPos)) {
                    Vec2f targetPos(mouseWorldPos.x, mouseWorldPos.y);
                    Room* nextRoomPtr = nullptr;

                    // Si el trigger es el primer salón va al parquesito
                    if (triggerName == "first") nextRoomPtr = &rooms["second"];
                    // Si el trigger es la parte de abajo del parquesito va al salón
                    else if (triggerName == "second_down") nextRoomPtr = &rooms["first"];
                    // else if (triggerName == "second_left") nextRoomPtr = &rooms["garage"]; por ver a la izq del parquesito

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
    // Eventos de presionar botón izquierdo
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);
        
        /* evento al clickar algo o alguien POR MODIFICAR
        if (rooms["second"].getEntity("mesa").sprite.getGlobalBounds().contains(clickPos)) {
                std::cout << "Clic en la mesa!" << std::endl;
                // Tocar la mesa desencadena el evento de un cuadro de diálogo
                showDialogue = true;
        } */
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
                // Aquí podrías cambiar de escena si nextSceneID no está vacío
                // Por ahora, el diálogo continuará con el siguiente en el stack
            }
            return;
        }
        // Si es diálogo normal, avanza la línea
        dialogueStack->advanceLine();
    }
}

void PastB::update(sf::Time dt)
{
    currentRoom->update(dt);
    GameManager::get().getPlayer().update(dt);

    if(currentRoom == &rooms["first"]){
        currentRoom->getNpc("nina").update(dt, currentRoom->getNavGrid());
    }

    if (m_pendingRoomSwitch && !GameManager::get().getPlayer().isMoving()) {
        if (m_pendingNextRoom) {
            m_previousRoom = currentRoom;
            currentRoom = m_pendingNextRoom;
            
            if (currentRoom == &rooms["first"]) {
                GameManager::get().getPlayer().setPosition(542.f, 446.f);
            } else if (currentRoom == &rooms["second"]) {
                if (m_previousRoom == &rooms["first"]) {
                    GameManager::get().getPlayer().setPosition(398.f, 200.f);
                }
            
            std::cout << "Switched room!" << std::endl;
            }
    }
        m_pendingRoomSwitch = false;
        m_pendingNextRoom = nullptr;
    }
}

void PastB::render(sf::RenderWindow& window)
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
            currentRoomTriggers.push_back("second_down");
        }
            //currentRoomTriggers.push_back("second_left"); // por ver a la izq del parquesito
        
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

    // Restaurar vista previa para dibujar diálogo
    window.setView(prevView);

    if (showDialogue && !dialogueStack->isStackEmpty()) {

        const DialogueSequence& currentDialogue = dialogueStack->getCurrentDialogue(); 

        dialogueUI.render(window, currentDialogue, currentDialogue.options, game->getSFMLFont(), dialogueStack->getCurrentLineIndex()); 
    }
}

void PastB::loadDialogs() {
    // 💡 Paso 1: Crea y puebla los DialogueLine.
    DialogueLine line1("", "...", "Pause");
    DialogueLine line2("Niña", "Hey, John! Vamos a jugar!", "Niña_01");
    DialogueLine line3("John Barr", "Jugar? Dónde estoy? Creo recordar algunas cosas...", "Main_Character");
    DialogueLine line4("", "Parece que suena el timbre del recreo... Todos deben salir de aquí.", "Sonido");
    
    // --- Secuencia 1: Diálogo Normal (tipo MONOLOGUE o NORMAL)
    DialogueSequence introDialogue(DialogueType::NORMAL);
    introDialogue.dialogueLines.emplace_back(line1);
    introDialogue.dialogueLines.emplace_back(line2);
    introDialogue.dialogueLines.emplace_back(line3);
    introDialogue.dialogueLines.emplace_back(line4);
    
    // --- Secuencia 2: Diálogo de Opción (tipo CHOICE)
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
    dialogueStack->pushDialogue(choiceDialogue);       // Se ejecuta SEGUNDO
    dialogueStack->pushDialogue(introDialogue);        // Se ejecuta PRIMERO
}