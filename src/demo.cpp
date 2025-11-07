#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Utils/GameUtilities.hpp" 
#include "Entities/Player.hpp"

int main() {
  
    sf::RenderWindow window(sf::VideoMode(800, 600), "Uchrony - Demo de Movimiento y Animación");
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/textures/suelo.png")) {} 
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Image collisionImage;
    if (!collisionImage.loadFromFile("assets/textures/escenario_colision.png")) {}

    sf::Texture mesaTexture;
    if (!mesaTexture.loadFromFile("assets/textures/mesa.png")) {}
    sf::Sprite mesaSprite(mesaTexture);

    sf::Texture mesaTexture_2;
    if (!mesaTexture_2.loadFromFile("assets/textures/mesa_2.png")) {}
    sf::Sprite mesaSprite_2(mesaTexture_2);

    sf::Texture bottellaTexture;
    if (!bottellaTexture.loadFromFile("assets/textures/botella.png")) {}
    sf::Sprite botellaSprite(bottellaTexture);

    //Creación de Entidades 
    Player player;
    player.setPosition(400.f, 300.f); // Establece su posición inicial
    player.getSprite().setScale(2.0f, 2.0f);
    backgroundSprite.setScale(1.0f, 1.0f);
    backgroundSprite.setPosition(0, 0);

    mesaSprite.setPosition(397, 494);
    mesaSprite.setOrigin(mesaTexture.getSize().x / 2.f, mesaTexture.getSize().y);
    mesaSprite.setScale(1.0f, 1.0f);

    mesaSprite_2.setPosition(743, 354);
    mesaSprite_2.setOrigin(mesaTexture.getSize().x / 2.f, mesaTexture.getSize().y);
    mesaSprite_2.setScale(1.0f, 1.0f);

    botellaSprite.setPosition(597, 185);



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
                    // if (mesaSprite.getGlobalBounds().contains(clickPos)) {
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

        player.update(dt, collisionImage);

        if (isDebugPlacing) {
            // MODO DEBUG
            GameUtils::debugFollowMouse(botellaSprite, window, "Posicion Objeto:");
        } else {
            // MODO JUEGO
            player.update(dt, collisionImage);
        }

        //Funciones de renderizado:
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
        
        //Funciones de depuración:

        //GameUtils::drawBoundingBox(window, player.getSprite(), sf::Color::Yellow); //Dibuja un cuadro alrededor de un objeto
        //GameUtils::drawBoundingBox(window, arbolSprite, sf::Color::Green);
        GameUtils::markPosition(window, player.getSprite().getPosition(), sf::Color::Red, 5.f); // Marca la posición del jugador
        GameUtils::markPosition(window, GameUtils::getMouseWorldPosition(window), sf::Color::Blue, 5.f); // Marca la posición del mouse
        GameUtils::drawBoundingBox(window, botellaSprite, sf::Color::Yellow);
        sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);
        //GameUtils::logPosition(clickPos, "Clic del mouse en");
        window.display();
    }

    return 0;
}