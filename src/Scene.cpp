#include "Scene.hpp"
#include <iostream>

Scene::Scene(std::string background_path, std::string collision_image_path) : background(background_path), player() {
    //inicio el player
    player.setPosition(400.f, 300.f); // Establece su posición inicial
    player.getSprite().setScale(2.0f, 2.0f);

    //inicio lo demás
    isDebugPlacing = false;
    
    if (!collision_image.loadFromFile(collision_image_path)) {
        std::cerr << "Error: No se pudo cargar la imagen de colision" << std::endl;
    }
}

Scene::~Scene()
{
    //Empty
}

void Scene::add_entity(const SpriteInfo& entity)
{
    entities.push_back(entity);
}

void Scene::handle_event(sf::Event event, sf::RenderWindow& window)
{
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

            if (clickPos_i.x >= 0 && clickPos_i.x < (int)collision_image.getSize().x &&
                    clickPos_i.y >= 0 && clickPos_i.y < (int)collision_image.getSize().y &&
                    collision_image.getPixel(clickPos_i.x, clickPos_i.y) == sf::Color::White) 
                    {
                player.moveTo(clickPos);
            }
            else if (clickPos_i.x >= 0 && clickPos_i.x < (int)collision_image.getSize().x &&
                    clickPos_i.y >= 0 && clickPos_i.y < (int)collision_image.getSize().y &&
                    collision_image.getPixel(clickPos_i.x, clickPos_i.y) == sf::Color::Red){
                    std::cout << "Zona prohibida!" << std::endl;
            }
        }
    }
}

void Scene::calculate(sf::RenderWindow& window)
{
    dt = clock.restart();
    player.update(dt, collision_image);

    /*if (isDebugPlacing) {
        // MODO DEBUG
        GameUtils::debugFollowMouse(entities["botella"].sprite, window, "Posicion Objeto:");
    }*/
}

void Scene::render(sf::RenderWindow& window)
{
    window.clear();
    window.draw(background.sprite);

    std::vector<sf::Sprite*> renderList;
    renderList.reserve(1 + entities.size());
    renderList.push_back(&player.getSprite());

    // Iterar por referencia: evitar tomar la dirección de una copia temporal
    for (auto &x : entities) {
        if (&x.sprite != nullptr) {
            renderList.push_back(&x.sprite);
        }
    }

    std::sort(renderList.begin(), renderList.end(),
        [](const sf::Sprite* a, const sf::Sprite* b) {
            return a->getPosition().y < b->getPosition().y;
        }
    );

    for (sf::Sprite* sprite : renderList) {
        window.draw(*sprite);
        // Comportamiento extra: si estamos dibujando la mesa, volvemos a dibujar la botella encima
    }

    window.display();
}