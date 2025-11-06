#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

// ¡Nuestros nuevos archivos!
#include "Utils/GameUtilities.hpp" // <- Ruta desde la carpeta 'Include'
#include "Entities/Player.hpp"

// --- Las constantes del jugador se han movido a Player.hpp ---


int main() {
    // --- 1. Creación de la Ventana ---
    sf::RenderWindow window(sf::VideoMode(800, 600), "Uchrony - Demo de Movimiento y Animación");
    window.setFramerateLimit(60);

    // --- 2. Carga de Recursos ---

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/textures/suelo.png")) { /* error */ } // <-- ARREGLADO
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Image collisionImage;
    if (!collisionImage.loadFromFile("assets/textures/escenario_colision.png")) { /* error */ } // <-- ARREGLADO

    sf::Texture mesaTexture;
    if (!mesaTexture.loadFromFile("assets/textures/mesa.png")) { /* error */ } // <-- ARREGLADO
    sf::Sprite mesaSprite(mesaTexture);

    // --- 3. Creación del Jugador y Objetos ---
    
    // ¡Crear el jugador ahora es así de simple!
    Player player;
    player.setPosition(400.f, 300.f); // Establece su posición inicial
    player.getSprite().setScale(2.0f, 2.0f);
    backgroundSprite.setScale(1.0f, 1.0f);
    backgroundSprite.setPosition(0, 0);

    // Configurar el árbol (como antes)
    mesaSprite.setPosition(397, 494);
    mesaSprite.setOrigin(mesaTexture.getSize().x / 2.f, mesaTexture.getSize().y);
    mesaSprite.setScale(1.0f, 1.0f);

    


    // --- 4. Variables de Animación ---
    // ¡YA NO SE NECESITAN! El jugador y el animador las manejan.
    bool isDebugPlacing = false; // ¿Estamos en modo "colocar objeto"?

    sf::Clock clock;

    // --- BUCLE PRINCIPAL DEL JUEGO ---
    while (window.isOpen()) {
        sf::Time dt = clock.restart();

        // --- 5. Manejo de Eventos (Inputs) ---
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::D) { // 'D' para Debug
                    isDebugPlacing = !isDebugPlacing; // Alterna el modo
                    
                    // Si apagamos el modo debug, limpia la consola
                    if (!isDebugPlacing) {
                        std::cout << std::endl << "Modo Debug DESACTIVADO." << std::endl;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    // ¡Usa nuestra utilidad!
                    sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);
                    sf::Vector2i clickPos_i(clickPos.x, clickPos.y);

                    // --- Lógica de Interacción (ejemplo) ---
                    // if (arbolSprite.getGlobalBounds().contains(clickPos)) {
                    //     std::cout << "Clic en el arbol!" << std::endl;
                    // }

                    // Comprobación de colisión del suelo
                    if (clickPos_i.x >= 0 && clickPos_i.x < (int)collisionImage.getSize().x &&
                         clickPos_i.y >= 0 && clickPos_i.y < (int)collisionImage.getSize().y &&
                         collisionImage.getPixel(clickPos_i.x, clickPos_i.y) == sf::Color::White) 
                    {
                        // ¡Solo le decimos al jugador A DÓNDE ir!
                        player.moveTo(clickPos);
                    }
                    else if (clickPos_i.x >= 0 && clickPos_i.x < (int)collisionImage.getSize().x &&
                         clickPos_i.y >= 0 && clickPos_i.y < (int)collisionImage.getSize().y &&
                         collisionImage.getPixel(clickPos_i.x, clickPos_i.y) == sf::Color::Red){
                            std::cout << "Zona prohibida!" << std::endl;
                    }
                }
            }

            // if (event.type == sf::Event::MouseButtonPressed) {
            //     if (event.mouseButton.button == sf::Mouse::Left) {
                    
            //         // ¡Usa nuestra utilidad!
            //         sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);
            //         sf::Vector2i clickPos_i(clickPos.x, clickPos.y);

            //         // --- Lógica de Interacción (ejemplo) ---
            //         if (arbolSprite.getGlobalBounds().contains(clickPos)) {
            //             std::cout << "Clic en el arbol!" << std::endl;
            //         }

            //         // Comprobación de colisión del suelo
            //         else if (clickPos_i.x >= 0 && clickPos_i.x < (int)collisionImage.getSize().x &&
            //                  clickPos_i.y >= 0 && clickPos_i.y < (int)collisionImage.getSize().y &&
            //                  collisionImage.getPixel(clickPos_i.x, clickPos_i.y) == sf::Color::White) 
            //         {
            //             // ¡Solo le decimos al jugador A DÓNDE ir!
            //             player.moveTo(clickPos);
            //         }
            //     }
            // }
        }

        // --- 6. Lógica de Actualización (Update) ---
        
        // ¡Actualizar al jugador ahora es una sola línea!
        // Él se encarga de su movimiento, colisión y animación.
        player.update(dt, collisionImage);

        if (isDebugPlacing) {
            // MODO DEBUG: Mueve la mesa con el mouse y muestra la posición
            GameUtils::debugFollowMouse(mesaSprite, window, "Posicion Objeto:");
        } else {
            // MODO JUEGO: Actualiza al jugador normalmente
            player.update(dt, collisionImage);
        }
        // --- 7. Dibujado (Render) ---
        window.clear();
        window.draw(backgroundSprite);

        // Y-Sorting (como antes, pero ahora usamos player.getSprite())
        std::vector<sf::Sprite*> renderList;
        renderList.push_back(&player.getSprite()); // Obtiene el sprite del jugador
        renderList.push_back(&mesaSprite);

        std::sort(renderList.begin(), renderList.end(), 
            [](const sf::Sprite* a, const sf::Sprite* b) {
                return a->getPosition().y < b->getPosition().y;
            }
        );

        for (sf::Sprite* sprite : renderList) {
            window.draw(*sprite);
        }
        
        // --- Dibujado de Utilidades (Opcional, para depurar) ---
        //GameUtils::drawBoundingBox(window, player.getSprite(), sf::Color::Yellow); //Dibuja un cuadro alrededor de un objeto

        //GameUtils::drawBoundingBox(window, arbolSprite, sf::Color::Green);
        GameUtils::markPosition(window, player.getSprite().getPosition(), sf::Color::Red, 5.f); // Marca la posición del jugador
        GameUtils::markPosition(window, GameUtils::getMouseWorldPosition(window), sf::Color::Blue, 5.f); // Marca la posición del mouse
        //GameUtils::drawBoundingBox(window, mesaSprite, sf::Color::Green);
        sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);
        //GameUtils::logPosition(clickPos, "Clic del mouse en");
        window.display();
    }

    return 0;
}