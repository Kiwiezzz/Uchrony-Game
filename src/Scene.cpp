#include "Scene.hpp"

Scene::Scene() : background("assets/textures/suelo.png") {
    isDebugPlacing = false;

    sf::Image collision_image;
    if (!collision_image.loadFromFile("assets/textures/escenario_colision.png")) {}

    SpriteInfo background("assets/textures/suelo.png");
    
    SpriteInfo mesa("assets/textures/mesa.png");
    mesa.sprite.setPosition(397, 494);
    mesa.sprite.setOrigin(mesa.texture.getSize().x / 2.f, mesa.texture.getSize().y);
    mesa.sprite.setScale(1.0f, 1.0f);

    list.push_back(mesa);

    SpriteInfo mesa2("assets/textures/mesa_2.png");
    mesa2.sprite.setPosition(743, 354);
    mesa2.sprite.setOrigin(mesa.texture.getSize().x / 2.f, mesa.texture.getSize().y);
    mesa2.sprite.setScale(1.0f, 1.0f);
    list.push_back(mesa2);

    SpriteInfo botella("assets/textures/botella.png");
    botella.sprite.setPosition(597, 185);
    list.push_back(botella);

    renderList.push_back(&(player.getSprite())); 
    renderList.push_back(&(list[0].sprite));
    renderList.push_back(&(list[1].sprite));
    renderList.push_back(&(list[2].sprite));
}

Scene::~Scene()
{
    //Empty
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
    player.update(dt, collision_image);

    if (isDebugPlacing) {
        // MODO DEBUG
        GameUtils::debugFollowMouse(list[2].sprite, window, "Posicion Objeto:");
    }
}

void Scene::render(sf::RenderWindow& window)
{
    window.clear();
    window.draw(background.sprite);
    

    std::sort(renderList.begin(), renderList.end(), 
        [](const sf::Sprite* a, const sf::Sprite* b) {
            return a->getPosition().y < b->getPosition().y;
        }
    );

    for (SpriteInfo x : list) {
        sf::Sprite sprite = x.sprite;
        window.draw(sprite);
        if (&sprite == &list[0].sprite) {
            window.draw(list[2].sprite);
        }
    }
    window.display();
}/**/