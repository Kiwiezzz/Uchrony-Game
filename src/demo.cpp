#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

// ¡Nuestros nuevos archivos!
#include "GameUtilities.hpp" // (Asumiendo que también usas el de la pregunta anterior)
#include "Player.hpp"

// --- Las constantes del jugador se han movido a Player.hpp ---


int main() {
    // --- 1. Creación de la Ventana ---
    sf::RenderWindow window(sf::VideoMode(800, 600), "Uchrony - Demo de Movimiento y Animación");
    window.setFramerateLimit(60);

    // --- 2. Carga de Recursos ---

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("suelo.png")) { /* error */ }
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Image collisionImage;
    if (!collisionImage.loadFromFile("escenario_colision.png")) { /* error */ }

    sf::Texture arbolTexture;
    if (!arbolTexture.loadFromFile("arbol.png")) { /* error */ }
    sf::Sprite arbolSprite(arbolTexture);

    // --- 3. Creación del Jugador y Objetos ---
    
    // ¡Crear el jugador ahora es así de simple!
    Player player;
    player.setPosition(400.f, 300.f); // Establece su posición inicial

    // Configurar el árbol (como antes)
    arbolSprite.setPosition(300.f, 250.f);
    arbolSprite.setOrigin(arbolTexture.getSize().x / 2.f, arbolTexture.getSize().y);
    arbolSprite.setScale(0.3f, 0.3f);


    // --- 4. Variables de Animación ---
    // ¡YA NO SE NECESITAN! El jugador y el animador las manejan.

    sf::Clock clock;

    // --- BUCLE PRINCIPAL DEL JUEGO ---
    while (window.isOpen()) {
        sf::Time dt = clock.restart();

        // --- 5. Manejo de Eventos (Inputs) ---
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    // ¡Usa nuestra utilidad!
                    sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);
                    sf::Vector2i clickPos_i(clickPos.x, clickPos.y);

                    // --- Lógica de Interacción (ejemplo) ---
                    if (arbolSprite.getGlobalBounds().contains(clickPos)) {
                         std::cout << "Clic en el arbol!" << std::endl;
                    }
                    // Comprobación de colisión del suelo
                    else if (clickPos_i.x >= 0 && clickPos_i.x < (int)collisionImage.getSize().x &&
                             clickPos_i.y >= 0 && clickPos_i.y < (int)collisionImage.getSize().y &&
                             collisionImage.getPixel(clickPos_i.x, clickPos_i.y) == sf::Color::White) 
                    {
                        // ¡Solo le decimos al jugador A DÓNDE ir!
                        player.moveTo(clickPos);
                    }
                }
            }
        }

        // --- 6. Lógica de Actualización (Update) ---
        
        // ¡Actualizar al jugador ahora es una sola línea!
        // Él se encarga de su movimiento, colisión y animación.
        player.update(dt, collisionImage);


        // --- 7. Dibujado (Render) ---
        window.clear();
        window.draw(backgroundSprite);

        // Y-Sorting (como antes, pero ahora usamos player.getSprite())
        std::vector<sf::Sprite*> renderList;
        renderList.push_back(&player.getSprite()); // Obtiene el sprite del jugador
        renderList.push_back(&arbolSprite);

        std::sort(renderList.begin(), renderList.end(), 
            [](const sf::Sprite* a, const sf::Sprite* b) {
                return a->getPosition().y < b->getPosition().y;
            }
        );

        for (sf::Sprite* sprite : renderList) {
            window.draw(*sprite);
        }
        
        // --- Dibujado de Utilidades (Opcional, para depurar) ---
        GameUtils::drawBoundingBox(window, player.getSprite(), sf::Color::Yellow);
        GameUtils::drawBoundingBox(window, arbolSprite, sf::Color::Green);


        window.display();
    }

    return 0;
}