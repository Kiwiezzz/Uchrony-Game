#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Utils/GameUtilities.hpp"
#include "Entities/Player.hpp"
#include "Utils/NavGrid.hpp"
#include "Utils/Pathfinder.hpp"
#include "Utils/Collision.hpp"

/*
 * demo.cpp
 * -------
 * Demo mínimo que muestra:
 * - Carga de recursos (texturas, imagen de colisión)
 * - Construcción de una `NavGrid` a partir de una imagen de colisión
 * - Uso del `Pathfinder` para generar rutas al hacer click
 * - Un bucle principal con manejo de eventos, actualización y render
 *
 * Notas:
 * - Las rutas relativas a `assets/` esperan que el ejecutable se lance
 *   desde la raíz del proyecto (o que la carpeta `assets/` esté visible
 *   desde el directorio de trabajo).
 */
/*
int main() {


    sf::RenderWindow window(sf::VideoMode(800, 600), "Uchrony - Demo de Movimiento y Animacion");
    window.setFramerateLimit(60);

    // Background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/textures/suelo.png")) {
        std::cerr << "Failed to load image \"assets/textures/suelo.png\". Reason: Unable to open file" << std::endl;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    // La colision mantiene la misma logica de una imagen de colision pero con la diferencia de que ahora
    // la clase NavGrid se encarga de interpretar la imagen de colision para generar una colision de tipo
    // rejilla adecuada para el pathfinding.
    sf::Image collisionImage;
    if (!collisionImage.loadFromFile("assets/textures/escenario_colision.png")) {
        std::cerr << "Error: No se pudo cargar assets/textures/escenario_colision.png" << std::endl;
        return -1;
    }

    // Carga de objetos
    sf::Texture mesaTexture;
    if (!mesaTexture.loadFromFile("assets/textures/mesa.png")) {}
    sf::Sprite mesaSprite(mesaTexture);

    sf::Texture mesaTexture_2;
    if (!mesaTexture_2.loadFromFile("assets/textures/mesa_2.png")) {}
    sf::Sprite mesaSprite_2(mesaTexture_2);

    sf::Texture bottellaTexture;
    if (!bottellaTexture.loadFromFile("assets/textures/botella.png")) {}
    sf::Sprite botellaSprite(bottellaTexture);

    //Uso de NavGrid y Pathfinder
    NavGrid navGrid(16); // tamaño de celda en píxeles
    if (!navGrid.buildFromImage(collisionImage)) {
        std::cerr << "Error: NavGrid::buildFromImage falló. Imagen inválida o tamaño incorrecto." << std::endl;
        return -1;
    }
    Pathfinder pathfinder;


    Player player;
    player.setPosition(400.f, 300.f); //Posicion Inicial
    player.getSprite().setScale(2.0f, 2.0f);

    backgroundSprite.setScale(1.0f, 1.0f);
    backgroundSprite.setPosition(0, 0);

    mesaSprite.setPosition(397, 494);
    mesaSprite.setOrigin(mesaTexture.getSize().x / 2.f, mesaTexture.getSize().y);

    mesaSprite_2.setPosition(743, 354);
    mesaSprite_2.setOrigin(mesaTexture.getSize().x / 2.f, mesaTexture.getSize().y);

    botellaSprite.setPosition(597, 185);

    bool isDebugPlacing = false; // Modo para colocar y seguir objetos con el mouse

    sf::Clock clock;

    //Game loop
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Eventos de mouse
            // Manejo de click izquierdo: intentamos generar una ruta
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Obtener posición del mouse en coordenadas del mundo
                    sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);

                    // Evento especial: si clicamos en la mesa, mostramos un mensaje
                    if (mesaSprite.getGlobalBounds().contains(clickPos)) {
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
        }

        // trigger de debug para colocar objetos con el mouse
        if (isDebugPlacing) {
            GameUtils::debugFollowMouse(botellaSprite, window, "Posicion Objeto:");
        } else {
            player.update(dt);
        }

        // Dibujo de sprites por orden en eje Y
        window.clear();
        window.draw(backgroundSprite);

        std::vector<sf::Sprite*> renderList;
        renderList.push_back(&player.getSprite());
        renderList.push_back(&botellaSprite);
        renderList.push_back(&mesaSprite);
        renderList.push_back(&mesaSprite_2);

        std::sort(renderList.begin(), renderList.end(),
            [](const sf::Sprite* a, const sf::Sprite* b) {
                return a->getPosition().y < b->getPosition().y;
            }
        );

        for (sf::Sprite* sprite : renderList) {
            window.draw(*sprite);
            if (sprite == &mesaSprite_2) {
                window.draw(botellaSprite);
            }
        }

        //Funciones de depuracion visual
        GameUtils::markPosition(window, player.getSprite().getPosition(), sf::Color::Red, 5.f);
        GameUtils::markPosition(window, GameUtils::getMouseWorldPosition(window), sf::Color::Blue, 5.f);
        GameUtils::drawBoundingBox(window, botellaSprite, sf::Color::Yellow);

        window.display();
    }

    return 0;
}

*/