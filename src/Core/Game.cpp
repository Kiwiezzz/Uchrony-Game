#include "Core/Game.hpp"



Game::Game() :
    mWindow(sf::VideoMode(800, 600), "Uchrony - Demo de Movimiento y Animacion"),
    background("assets/textures/suelo.png"),
    collision("assets/textures/escenario_colision.png"),
    navGrid(16)
{    
    using namespace std;
    
    mWindow.setFramerateLimit(60);
    
    // Carga de objetos
    objects["mesa"] = SpriteAsset("assets/textures/mesa.png");
    objects["mesa2"] = SpriteAsset("assets/textures/mesa_2.png");
    objects["botella"] = SpriteAsset("assets/textures/botella.png");

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
    
    // Configuración del inventario
    if (!slotTex.loadFromFile("assets/textures/Inventory.png")) {
        std::cerr << "Warning: no se cargo assets/textures/Inventory.png" << std::endl;
    }
    inventory = Inventory(slotTex, 0, 0, 4, 8.f);
    inventory.setDisplayScale(0.35f);
    
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

    inventory.insertAt(0, bottleItem);
    inventory.insertAt(1, guitarItem);
    inventory.insertAt(2, lentesItem);
    inventory.insertAt(3, ocarinaItem);
    
    int draggingFrom;

    background.sprite.setScale(1.0f, 1.0f);
    background.sprite.setPosition(0, 0);

    mesa.sprite.setPosition(397, 494);
    mesa.sprite.setOrigin(mesa.texture.getSize().x / 2.f, mesa.texture.getSize().y);

    mesa2.sprite.setPosition(743, 354);
    mesa2.sprite.setOrigin(mesa.texture.getSize().x / 2.f, mesa.texture.getSize().y);

    botella.sprite.setPosition(597, 185);

    isDebugPlacing = false; // Modo para colocar y seguir objetos con el mouse

   
}


void Game::run()
{
    while (mWindow.isOpen())
    {
        handleEvents();
        update();
        render();
    }
    
}

void Game::handleEvents()
{
    sf::Event event;
        while (mWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mWindow.close();
            }

            // Eventos de mouse
            // Manejo de click izquierdo: intentamos generar una ruta
            if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                                // CLICK IZQUIERDO: activar evento del item si clicó en UI, o generar ruta en el mundo
                                sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);
                                int uiIdx = inventory.indexAtScreenPos(mouseWinPos, mWindow);
                                if (uiIdx >= 0) {
                                    const Item* it = inventory.itemAt((unsigned)uiIdx);
                                    if (it) {
                                        it->onClick();
                                        // Si es la ocarina (id == 4) reproducir sonido
                                        if (it->id() == 4) {
                                            ocarinaSound.stop();
                                            ocarinaSound.play();
                                        }
                                    }
                                    continue;
                                }
                    // Obtener posición del mouse en coordenadas del mundo
                    sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(mWindow);

                    // Evento especial: si clicamos en la mesa, mostramos un mensaje
                    if (objects["mesa"].sprite.getGlobalBounds().contains(clickPos)) {
                        std::cout << "Clic en la mesa!" << std::endl;
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
                    int uiIdx = inventory.indexAtScreenPos(mouseWinPos, mWindow);
                    if (uiIdx >= 0) {
                        draggingItem = inventory.pickAt(uiIdx);
                        if (draggingItem) draggingFrom = uiIdx;
                        continue;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Right && draggingItem) {
                    sf::Vector2i mouseWinPos(event.mouseButton.x, event.mouseButton.y);
                    int idx = inventory.indexAtScreenPos(mouseWinPos, mWindow);
                    if (idx >= 0) {
                        inventory.insertAt(idx, *draggingItem);
                    } else {
                        inventory.insertAt(draggingFrom >= 0 ? (unsigned)draggingFrom : inventory.size(), *draggingItem);
                    }
                    draggingItem.reset();
                    draggingFrom = -1;
                }
            }
        }
}

void Game::update()
{
    sf::Time dt = clock.restart();

    // trigger de debug para colocar objetos con el mouse
    if (isDebugPlacing) {
        GameUtils::debugFollowMouse(objects["botella"].sprite, mWindow, "Posicion Objeto:");
    } else {
        player.update(dt);
    }
}

void Game::render()
{
    // Dibujo de sprites por orden en eje Y
        mWindow.clear();
        mWindow.draw(background.sprite);

        std::vector<sf::Sprite*> renderList;
        renderList.push_back(&player.getSprite());
        renderList.push_back(&objects["botella"].sprite);
        renderList.push_back(&objects["mesa"].sprite);
        renderList.push_back(&objects["mesa2"].sprite);

        std::sort(renderList.begin(), renderList.end(),
            [](const sf::Sprite* a, const sf::Sprite* b) {
                return a->getPosition().y < b->getPosition().y;
            }
        );

        for (sf::Sprite* sprite : renderList) {
            mWindow.draw(*sprite);
            if (sprite == &objects["mesa2"].sprite) {
                mWindow.draw(objects["botella"].sprite);
            }
        }

        //Funciones de depuracion visual
        GameUtils::markPosition(mWindow, player.getSprite().getPosition(), sf::Color::Red, 5.f);
        GameUtils::markPosition(mWindow, GameUtils::getMouseWorldPosition(mWindow), sf::Color::Blue, 5.f);
        GameUtils::drawBoundingBox(mWindow, objects["botella"].sprite, sf::Color::Yellow);

        // DIBUJO UI (inventario) en vista por defecto para que quede fija en pantalla
        auto prevView = mWindow.getView();
        mWindow.setView(mWindow.getDefaultView());
        sf::Vector2u ws = mWindow.getSize();
        float margin = 8.f;
        // Usar la altura de slot ya escalada para posicionar correctamente el inventario
        inventory.setBasePosition({ margin, float(ws.y) - margin - float(inventory.displaySlotHeight()) });
        inventory.draw(mWindow);

        // Dibujar item arrastrado bajo el mouse
        if (draggingItem) {
            sf::Vector2i mp = sf::Mouse::getPosition(mWindow);
            // SOLO dibujamos el sprite del item (no el fondo del slot)
            sf::Sprite s = draggingItem->sprite();
            sf::FloatRect gb = s.getGlobalBounds();
            s.setPosition(float(mp.x) - gb.width/2.f, float(mp.y) - gb.height/2.f);
            mWindow.draw(s);
        }

        mWindow.setView(prevView);

        mWindow.display();
}
