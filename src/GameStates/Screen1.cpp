#include "GameStates/Screen1.hpp"
#include "GameStates/Dialogue1.hpp"
#include "../Include/Core/Game.hpp"
#include "../Include/Classes/GameManager.hpp"

Screen1::Screen1() {
    init();
}

void Screen1::init()    
{    
    using namespace std;
    
    // Inicialización de variables y carga de recursos de dialogo
    dialogue1.init();
    dialogue1.setGame(this->game);
    
    background = SpriteAsset("assets/textures/suelo.png"),
    collision = ImageAsset("assets/textures/escenario_colision.png"),
    navGrid = NavGrid(16);

    // Carga de objetos
    objects["mesa"] = SpriteAsset("assets/textures/mesa.png");
    objects["mesa2"] = SpriteAsset("assets/textures/mesa_2.png");
    objects["botella"] = SpriteAsset("assets/textures/botella.png");

    npc.init("assets/textures/npc_spritesheet.png", Vec2f(400.f, 300.f), true);
    //npc.getSprite().setScale(2.0f, 2.0f);
    //npc.setupAnimations(); // Private now
    npc.addAnimation("Posicion_Espalda", 0, 1, 2.0f, false, 2);
    npc.addAnimation("Posicion_Espalda2", 0, 1, 2.0f, false, 5);
    //row(r), frameCount(fc), duration(d), loop(l), startColumn(sc)
    
    
    

    auto& mesa = objects["mesa"];
    auto& mesa2 = objects["mesa2"];
    auto& botella = objects["botella"];
    
    // La colision mantiene la misma logica de una imagen de colision pero con la diferencia de que ahora
    // la clase NavGrid se encarga de interpretar la imagen de colision para generar una colision de tipo
    // rejilla adecuada para el pathfinding.

    //Uso de NavGrid y Pathfinder //El pathdinder y el otro están declarados globalmente
    if (!navGrid.buildFromImage(collision.image)) {
        std::cerr << "Error: NavGrid::buildFromImage falló. Imagen inválida o tamaño incorrecto." << std::endl;
        //DEBERÍA CERRARSE
    }


    player.setPosition(400.f, 300.f); //Posicion Inicial
    player.getSprite().setScale(2.0f, 2.0f);
    
    // Añadir items de ejemplo: botella, guitarra, lentes, ocarina
    // Cargar texturas de items
    items["guitarra"] = TextureAsset("assets/textures/Guitarra.png");
    items["lentes"] = TextureAsset("assets/textures/lentes.png");
    items["ocarina"] = TextureAsset("assets/textures/Ocarina.png");

    // Cargar sonido de la ocarina (se usará al hacer click izquierdo sobre el item)
    
    if (!ocarinaBuffer.loadFromFile("assets/sounds/ocarina.mp3")) {
        std::cerr << "Warning: no se cargo assets/sounds/ocarina.mp3" << std::endl;
    }
    
    ocarinaSound.setBuffer(ocarinaBuffer);

    Item bottleItem(1, botella.texture);
    bottleItem.sprite().setScale(0.1f, 0.1f); // Escala personalizada para la botella
    Item guitarItem(2, items["guitarra"].texture);
    guitarItem.sprite().setScale(0.05f, 0.05f);
    Item lentesItem(3, items["lentes"].texture);
    lentesItem.sprite().setScale(0.05f, 0.05f);
    Item ocarinaItem(4, items["ocarina"].texture);
    ocarinaItem.sprite().setScale(0.1f, 0.1f);

    GameManager::get().getInventory().insertAt(0, bottleItem);
    GameManager::get().getInventory().insertAt(1, guitarItem);
    GameManager::get().getInventory().insertAt(2, lentesItem);
    GameManager::get().getInventory().insertAt(3, ocarinaItem);
    
    

    background.sprite.setScale(1.0f, 1.0f);
    background.sprite.setPosition(0, 0);

    mesa.sprite.setPosition(397, 494);
    mesa.sprite.setOrigin(float(mesa.texture.getSize().x) / 2.f, float(mesa.texture.getSize().y));
    mesa.setlayer(0);

    mesa2.sprite.setPosition(673, 284);
    mesa2.sprite.setOrigin(float(mesa2.texture.getSize().x) / 2.f, float(mesa2.texture.getSize().y));
    mesa2.setlayer(0);

    botella.sprite.setPosition(597, 185);
    botella.setlayer(1); // la botella debe renderizarse por encima de la mesa

    isDebugPlacing = false; // Modo para colocar y seguir objetos con el mouse

}

void Screen1::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    // Eventos de mouse
    // Manejo de click izquierdo: intentamos generar una ruta
    if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                        // CLICK IZQUIERDO: activar evento del item si clicó en UI, o generar ruta en el mundo
                        sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);

                        int uiIdx = GameManager::get().getInventory().indexAtScreenPos(mouseWinPos, window);
                        if (uiIdx >= 0) {
                            const Item* it = GameManager::get().getInventory().itemAt((unsigned)uiIdx);
                            if (it) {
                                it->onClick();
                                // Si es la ocarina (id == 4) reproducir sonido
                                if (it->id() == 4) {
                                    ocarinaSound.stop();
                                    ocarinaSound.play();
                                }
                            }
                            return;
                        }
            // Obtener posición del mouse en coordenadas del mundo
            sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);

            // Evento especial: si clicamos en la mesa, mostramos un mensaje
            if (objects["mesa"].sprite.getGlobalBounds().contains(clickPos)) {
                std::cout << "Clic en la mesa!" << std::endl;
                // Tocar la mesa desencadena el evento de un cuadro de diálogo

                // CAMBIAR ESTADO A DIALOGO esto borra el estado actual y pone el de dialogo
                //this->game->changeState(new Dialogue1());
                showDialogue = true;
            } 
            else 
            {
                //Si no hay un evento en especial, procedemos a calcular la ruta
                Point start = navGrid.worldToGrid(player.getPosition());
                Point end = navGrid.worldToGrid(Vec2f(clickPos.x, clickPos.y));

                if (navGrid.isWalkable(end)) {
                    std::vector<Point> path = pathfinder.findPath(navGrid, start, end);
                    if (!path.empty()) {
                        // Pasar la ruta al jugador para que la siga
                        player.setPath(path, navGrid);
                    } else {
                        std::cout << "No se encontro ruta!" << std::endl;
                    }
                } 
                //Zona de la puerta no caminable
                else {
                    std::cout << "Zona prohibida!" << std::endl;
                }
            }
        }
    }

    // CLICK DERECHO: iniciar/soltar drag de items en UI
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

void Screen1::update(sf::Time dt)
{
    // trigger de debug para colocar objetos con el mouse
    if (!isDebugPlacing){
        player.update(dt);
        npc.update(dt, navGrid);
    }
}

void Screen1::render(sf::RenderWindow& window)
{
    if(isDebugPlacing)
    GameUtils::debugFollowMouse(objects["botella"].sprite, window, "Posicion Objeto:");

    window.draw(background.sprite);

    struct RenderEntry { sf::Sprite* sprite; int layer; };
    std::vector<RenderEntry> renderList;

    renderList.push_back({ &player.getSprite(), 0 });
    renderList.push_back({ &npc.getSprite(), 0 });

    // Añadir objetos del mapa usando su campo `layer`
    for (auto& kv : objects) {
        renderList.push_back({ &kv.second.sprite, kv.second.layer });
    }

    //Ordenamiento por capas y posición Y: Primero se dibuja los objetos
    //cuya capa estap or encima del resto, y luego por los que estan en una 
    //posición Y mayor (más abajo en pantalla).
    std::sort(renderList.begin(), renderList.end(),
        [](const RenderEntry& a, const RenderEntry& b) {
            if (a.layer != b.layer) return a.layer < b.layer;
            return a.sprite->getPosition().y < b.sprite->getPosition().y;
        }
    );

    for (const auto& e : renderList) {
        window.draw(*e.sprite);
    }

    //Funciones de depuracion visual
    /*GameUtils::markPosition(window, player.getSprite().getPosition(), sf::Color::Red, 5.f);
    GameUtils::markPosition(window, GameUtils::getMouseWorldPosition(window), sf::Color::Blue, 5.f);
    GameUtils::drawBoundingBox(window, objects["botella"].sprite, sf::Color::Yellow);*/

    // DIBUJO UI (inventario) en vista por defecto para que quede fija en pantalla
    auto prevView = window.getView();
    window.setView(window.getDefaultView());
    sf::Vector2u ws = window.getSize();
    float margin = 8.f;
    // Usar la altura de slot ya escalada para posicionar correctamente el inventario
    GameManager::get().getInventory().setBasePosition({ margin, float(ws.y) - margin - float(GameManager::get().getInventory().displaySlotHeight()) });
    GameManager::get().getInventory().draw(window);

    // Dibujar item arrastrado bajo el mouse (ahora manejado por Inventory::draw)
    if (draggingItem) {
        sf::Vector2i mp = sf::Mouse::getPosition(window);
        // SOLO dibujamos el sprite del item (no el fondo del slot)
        sf::Sprite s = draggingItem->sprite();
        sf::FloatRect gb = s.getGlobalBounds();
        s.setPosition(float(mp.x) - gb.width/2.f, float(mp.y) - gb.height/2.f);
        window.draw(s);
    }

    // Restaurar vista previa para dibujar diálogo
    window.setView(prevView);

    if (showDialogue) {
        dialogue1.render(window); 
    }
}