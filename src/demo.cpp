/*#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Utils/GameUtilities.hpp" 
#include "Entities/Player.hpp"
#include "SpriteInfo.hpp"


int main() {
  
    sf::RenderWindow window(sf::VideoMode(800, 600), "Uchrony - Demo de Movimiento y Animacion");
    window.setFramerateLimit(60);

    SpriteInfo background("assets/textures/suelo.png");

    sf::Image collisionImage;
    if (!collisionImage.loadFromFile("assets/textures/escenario_colision.png")) {}

    SpriteInfo mesa("assets/textures/mesa.png");

    SpriteInfo mesa2("assets/textures/mesa_2.png");

    SpriteInfo botella("assets/textures/botella.png");

    //Creación de Entidades 
    Player player;
    player.setPosition(400.f, 300.f); // Establece su posición inicial
    player.getSprite().setScale(2.0f, 2.0f);

    mesa.sprite.setPosition(397, 494);
    mesa.sprite.setOrigin(mesa.texture.getSize().x / 2.f, mesa.texture.getSize().y);
    mesa.sprite.setScale(1.0f, 1.0f);

    mesa2.sprite.setPosition(743, 354);
    mesa2.sprite.setOrigin(mesa.texture.getSize().x / 2.f, mesa.texture.getSize().y);
    mesa2.sprite.setScale(1.0f, 1.0f);

    botella.sprite.setPosition(597, 185);



    bool isDebugPlacing = false; // ¿Estamos en modo "colocar objeto"?

    sf::Clock clock;

    //Bucle del juego principal
    while (window.isOpen()) {
        sf::Time dt = clock.restart();

        //Manejo de Eventos (inputs)
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
                    
                    // Obtener la posición del clic en coordenadas del mundo
                    sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);
                    sf::Vector2i clickPos_i(clickPos.x, clickPos.y);

                    // --- Lógica de Interacción (ejemplo) ---
                    // if (mesa.getGlobalBounds().contains(clickPos)) {
                    //     std::cout << "Clic en el arbol!" << std::endl;
                    // }

                    if (clickPos_i.x >= 0 && clickPos_i.x < (int)collisionImage.getSize().x &&
                         clickPos_i.y >= 0 && clickPos_i.y < (int)collisionImage.getSize().y &&
                         collisionImage.getPixel(clickPos_i.x, clickPos_i.y) == sf::Color::White) 
                    {
                        player.moveTo(clickPos);
                    }
                    else if (clickPos_i.x >= 0 && clickPos_i.x < (int)collisionImage.getSize().x &&
                         clickPos_i.y >= 0 && clickPos_i.y < (int)collisionImage.getSize().y &&
                         collisionImage.getPixel(clickPos_i.x, clickPos_i.y) == sf::Color::Red){
                            std::cout << "Zona prohibida!" << std::endl;
                    }
                }
            }
        }

        if (isDebugPlacing) {
            // MODO DEBUG
            GameUtils::debugFollowMouse(botella.sprite, window, "Posicion Objeto:");
        } else {
            // MODO JUEGO
            player.update(dt, collisionImage);
        }

        //Funciones de renderizado:
        window.clear();
        window.draw(background.sprite);


        std::vector<sf::Sprite*> renderList;
        renderList.push_back(&(player.getSprite())); 
        renderList.push_back(&(botella.sprite));
        renderList.push_back(&(mesa.sprite));
        renderList.push_back(&(mesa.sprite));
        

        std::sort(renderList.begin(), renderList.end(), 
            [](const sf::Sprite* a, const sf::Sprite* b) {
                return a->getPosition().y < b->getPosition().y;
            }
        );

        for (sf::Sprite* sprite : renderList) {
            window.draw(*sprite);
            if (sprite == &(mesa.sprite)) {
                window.draw(botella.sprite);
            }
        }
        
        //Funciones de depuración:

        //GameUtils::drawBoundingBox(window, player.getSprite(), sf::Color::Yellow); //Dibuja un cuadro alrededor de un objeto
        //GameUtils::drawBoundingBox(window, arbolSprite, sf::Color::Green);
        GameUtils::markPosition(window, player.getSprite().getPosition(), sf::Color::Red, 5.f); // Marca la posición del jugador
        GameUtils::markPosition(window, GameUtils::getMouseWorldPosition(window), sf::Color::Blue, 5.f); // Marca la posición del mouse
        GameUtils::drawBoundingBox(window, botella.sprite, sf::Color::Yellow);
        sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);
        //GameUtils::logPosition(clickPos, "Clic del mouse en");
        window.display();
    }

    return 0;
}/**/