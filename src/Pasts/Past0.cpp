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
    
    ObjectRoom* mesa2 = new ObjectRoom("assets/textures/mesa_2.png");
    mesa2->sprite.setPosition(673, 284);
    mesa2->sprite.setOrigin(float(mesa2->texture.getSize().x) / 2.f, float(mesa2->texture.getSize().y));
    mesa2->setlayer(0);
    secondRoom.addEntity("mesa2", mesa2);

    ObjectRoom* botella = new ObjectRoom("assets/textures/botella.png");
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

    // ============================================================
    // CONFIGURACIÓN DE TRIGGERS DE PUERTAS
    // ============================================================
    // Los triggers son rectángulos invisibles que activan el cambio de habitación
    // cuando el jugador hace clic en ellos
    // Formato: sf::FloatRect(x, y, ancho, alto)
    
    // Cuarto: Solo tiene 1 puerta (arriba) que va al laboratorio
    doorTriggers["first"] = sf::FloatRect(477.f, 446.f, 150.f, 120.f);
    
    // Laboratorio: Tiene 4 puertas (arriba, derecha, abajo, izquierda)
    doorTriggers["second_up"] = sf::FloatRect(358.f, 93.f, 80.f, 120.f);      // → Cuarto
    doorTriggers["second_right"] = sf::FloatRect(720.f, 250.f, 80.f, 600.f);  // → Baño
    doorTriggers["second_down"] = sf::FloatRect(230.f, 520.f, 400.f, 80.f);   // → Patio
    doorTriggers["second_left"] = sf::FloatRect(0.f, 250.f, 80.f, 600.f);     // → Garage
    
    // Cada habitación secundaria tiene 1 puerta de regreso al laboratorio
    doorTriggers["bathroom"] = sf::FloatRect(0.f, 250.f, 100.f, 300.f);       // Baño → Lab
    doorTriggers["patio"] = sf::FloatRect(520.f, 100.f, 100.f, 110.f);        // Patio → Lab
    doorTriggers["garage"] = sf::FloatRect(720.f, 250.f, 80.f, 80.f);         // Garage → Lab
   
    // Establecer el cuarto como habitación inicial
    currentRoom = &rooms["first"];
    
    // Configurar posición y escala inicial del jugador
    auto& GM = GameManager::get();
    GM.getPlayer().setPosition(400.f, 300.f);
    GM.getPlayer().getSprite().setScale(2.0f, 2.0f);
}

/**
 * @brief Maneja todos los eventos de entrada del usuario
 * 
 * Principales funcionalidades:
 * - Detección de clics en puertas para cambiar de habitación
 * - Interacción con items del inventario
 * - Drag & drop de items entre slots del inventario
 * - Modo debug para ajustar posiciones de triggers (tecla D)
 */
void Past0::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    // ============================================================
    // MODO DEBUG: Activar/desactivar con la tecla D
    // ============================================================
    // Cuando está activo, muestra los triggers de puertas como rectángulos rojos
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
        isDebugPlacing = !isDebugPlacing;
        std::cout << "Debug mode: " << (isDebugPlacing ? "ON" : "OFF") << std::endl;
    }
    
    // ============================================================
    // MANEJO DE CLICK IZQUIERDO
    // ============================================================
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);
        
        // --- Prioridad 1: Interacción con inventario ---
        int uiIdx = GameManager::get().getInventory().indexAtScreenPos(mouseWinPos, window);
        if (uiIdx >= 0) {
            const Item* it = GameManager::get().getInventory().itemAt((unsigned)uiIdx);
            if (it) it->onClick();
            return;  // No procesar más eventos si clickeamos el inventario
        }
        
        // --- Prioridad 2: Interacción con puertas (solo si NO estamos en debug) ---
        if (!isDebugPlacing) {
            sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mouseWinPos);
            
            // IMPORTANTE: Determinar qué triggers pertenecen a la habitación ACTUAL
            // Esto evita conflictos cuando dos triggers se solapan en diferentes habitaciones
            std::vector<std::string> currentRoomTriggers;
            
            if (currentRoom == &rooms["first"]) {
                currentRoomTriggers.push_back("first");
            } else if (currentRoom == &rooms["second"]) {
                // El laboratorio tiene 4 puertas diferentes
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
            
            // Chequear SOLO los triggers de la habitación actual
            for (const auto& triggerName : currentRoomTriggers) {
                if (doorTriggers.count(triggerName) && doorTriggers[triggerName].contains(mouseWorldPos)) {
                    Vec2f targetPos(mouseWorldPos.x, mouseWorldPos.y);
                    Room* nextRoomPtr = nullptr;

                    // Definir a qué habitación va cada puerta
                    if (triggerName == "first") nextRoomPtr = &rooms["second"];
                    else if (triggerName == "second_up") nextRoomPtr = &rooms["first"];
                    else if (triggerName == "second_right") nextRoomPtr = &rooms["bathroom"];
                    else if (triggerName == "second_down") nextRoomPtr = &rooms["patio"];
                    else if (triggerName == "second_left") nextRoomPtr = &rooms["garage"];
                    else if (triggerName == "bathroom") nextRoomPtr = &rooms["second"];
                    else if (triggerName == "patio") nextRoomPtr = &rooms["second"];
                    else if (triggerName == "garage") nextRoomPtr = &rooms["second"];

                    if (nextRoomPtr) {
                        // Verificar que el punto clickeado sea caminable
                        auto& navGrid = currentRoom->getNavGrid();
                        Point start = navGrid.worldToGrid(GameManager::get().getPlayer().getPosition());
                        Point end = navGrid.worldToGrid(targetPos);
                        
                        if (navGrid.isWalkable(end)) {
                            // Calcular ruta desde la posición actual hasta la puerta
                            std::vector<Point> path = pathfinder.findPath(navGrid, start, end);
                            if (!path.empty()) {
                                GameManager::get().getPlayer().setPath(path, navGrid);
                                m_pendingRoomSwitch = true;
                                m_pendingNextRoom = nextRoomPtr;
                                std::cout << "Walking to door (" << triggerName << ")..." << std::endl;
                            }
                        }
                        return;  // Salir después de procesar el trigger
                    }
                }
            }

            // Si no clickeamos una puerta, cancelar cualquier cambio pendiente
            m_pendingRoomSwitch = false;
            m_pendingNextRoom = nullptr;
            
            // Pasar el evento a la habitación para interacciones con objetos
            if (currentRoom) currentRoom->handleEvent(event, window);
        }
    }

    // ============================================================
    // DRAG & DROP DE ITEMS EN INVENTARIO
    // ============================================================
    
    // --- Iniciar arrastre con click derecho ---
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
        sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);
        int uiIdx = GameManager::get().getInventory().indexAtScreenPos(mouseWinPos, window);
        if (uiIdx >= 0) {
            draggingItem = GameManager::get().getInventory().pickAt(uiIdx);
            if (draggingItem) draggingFrom = uiIdx;
        }
    }

    // --- Soltar item al liberar click derecho ---
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right && draggingItem) {
        sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);
        int idx = GameManager::get().getInventory().indexAtScreenPos(mouseWinPos, window);
        
        if (idx >= 0) {
            // Soltar en un slot específico
            GameManager::get().getInventory().insertAt(idx, *draggingItem);
        } else {
            // Soltar fuera del inventario: devolver al slot original
            GameManager::get().getInventory().insertAt(
                draggingFrom >= 0 ? (unsigned)draggingFrom : GameManager::get().getInventory().size(), 
                *draggingItem
            );
        }
        draggingItem.reset();
        draggingFrom = -1;
    }
}

/**
 * @brief Actualiza la lógica del juego cada frame
 * 
 * Responsabilidades:
 * - Actualizar la habitación actual (animaciones, NPCs, etc.)
 * - Actualizar el jugador (movimiento, animaciones)
 * - Detectar cuándo el jugador llegó a una puerta y cambiar de habitación
 */
void Past0::update(sf::Time dt)
{
    currentRoom->update(dt);
    GameManager::get().getPlayer().update(dt);

    // ============================================================
    // SISTEMA DE CAMBIO DE HABITACIÓN
    // ============================================================
    // Solo cambiar de habitación cuando:
    // 1. Hay un cambio pendiente (m_pendingRoomSwitch)
    // 2. El jugador ya NO se está moviendo (llegó a la puerta)
    if (m_pendingRoomSwitch && !GameManager::get().getPlayer().isMoving()) {
        if (m_pendingNextRoom) {
            // Guardar de qué habitación venimos (para saber en qué puerta aparecer)
            m_previousRoom = currentRoom;
            
            // Cambiar a la nueva habitación
            currentRoom = m_pendingNextRoom;
            
            // ============================================================
            // POSICIONES DE SPAWN AL ENTRAR A CADA HABITACIÓN
            // ============================================================
            
            if (currentRoom == &rooms["first"]) {
                // Entrando al cuarto desde el laboratorio
                GameManager::get().getPlayer().setPosition(542.f, 446.f);
                
            } else if (currentRoom == &rooms["second"]) {
                // Entrando al laboratorio: depende de dónde venimos
                if (m_previousRoom == &rooms["first"]) {
                    // Venimos del cuarto → aparecer en puerta de arriba
                    GameManager::get().getPlayer().setPosition(398.f, 200.f);
                } else if (m_previousRoom == &rooms["bathroom"]) {
                    // Venimos del baño → aparecer en puerta derecha
                    GameManager::get().getPlayer().setPosition(680.f, 400.f);
                } else if (m_previousRoom == &rooms["patio"]) {
                    // Venimos del patio → aparecer en puerta de abajo
                    GameManager::get().getPlayer().setPosition(400.f, 520.f);
                } else if (m_previousRoom == &rooms["garage"]) {
                    // Venimos del garage → aparecer en puerta izquierda
                    GameManager::get().getPlayer().setPosition(120.f, 300.f);
                }
                
            } else if (currentRoom == &rooms["bathroom"]) {
                // Entrando al baño
                GameManager::get().getPlayer().setPosition(100.f, 450.f);
                
            } else if (currentRoom == &rooms["patio"]) {
                // Entrando al patio
                GameManager::get().getPlayer().setPosition(570.f, 140.f);
                
            } else if (currentRoom == &rooms["garage"]) {
                // Entrando al garage
                GameManager::get().getPlayer().setPosition(700.f, 300.f);
            }
            
            std::cout << "Switched room!" << std::endl;
        }
        
        // Resetear el estado de cambio
        m_pendingRoomSwitch = false;
        m_pendingNextRoom = nullptr;
    }
}

/**
 * @brief Renderiza todo en pantalla
 * 
 * Orden de renderizado:
 * 1. Habitación actual (fondo, objetos, NPCs)
 * 2. Triggers de debug (solo si está activo)
 * 3. Interfaz de usuario (inventario)
 * 4. Item siendo arrastrado
 */
void Past0::render(sf::RenderWindow& window)
{
    // Renderizar la habitación actual
    currentRoom->render(window);
    
    // ============================================================
    // MODO DEBUG: Visualizar triggers de puertas
    // ============================================================
    if (isDebugPlacing) {
        std::vector<std::string> currentRoomTriggers;
        
        // Obtener triggers de la habitación actual
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
        
        // Dibujar cada trigger como un rectángulo rojo semi-transparente
        for (const auto& triggerName : currentRoomTriggers) {
            if (doorTriggers.count(triggerName)) {
                sf::RectangleShape debugRect;
                debugRect.setPosition(doorTriggers[triggerName].left, doorTriggers[triggerName].top);
                debugRect.setSize(sf::Vector2f(doorTriggers[triggerName].width, doorTriggers[triggerName].height));
                debugRect.setFillColor(sf::Color(255, 0, 0, 80));  // Rojo semi-transparente
                debugRect.setOutlineColor(sf::Color::Red);
                debugRect.setOutlineThickness(2.f);
                window.draw(debugRect);
            }
        }
        
        // Mostrar coordenadas del trigger bajo el mouse
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        for (const auto& triggerName : currentRoomTriggers) {
            if (doorTriggers.count(triggerName) && doorTriggers[triggerName].contains(mousePos)) {
                std::cout << "Trigger [" << triggerName << "]: (" 
                          << doorTriggers[triggerName].left << ", " 
                          << doorTriggers[triggerName].top << ", " 
                          << doorTriggers[triggerName].width << ", " 
                          << doorTriggers[triggerName].height << ")" << std::endl;
            }
        }
    }
    
    // ============================================================
    // RENDERIZAR INTERFAZ DE USUARIO (UI)
    // ============================================================
    // La UI usa la vista por defecto para quedar fija en pantalla
    auto prevView = window.getView();
    window.setView(window.getDefaultView());
    
    // Posicionar inventario en la parte inferior de la pantalla
    sf::Vector2u ws = window.getSize();
    float margin = 8.f;
    GameManager::get().getInventory().setBasePosition({ 
        margin, 
        float(ws.y) - margin - float(GameManager::get().getInventory().displaySlotHeight()) 
    });
    GameManager::get().getInventory().draw(window);

    // Dibujar item siendo arrastrado (si existe)
    if (draggingItem) {
        sf::Vector2i mp = sf::Mouse::getPosition(window);
        sf::Sprite s = draggingItem->sprite();
        sf::FloatRect gb = s.getGlobalBounds();
        s.setPosition(float(mp.x) - gb.width/2.f, float(mp.y) - gb.height/2.f);
        window.draw(s);
    }

    // Restaurar la vista anterior
    window.setView(prevView);
}