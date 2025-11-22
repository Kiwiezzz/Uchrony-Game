#include "Game.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "Uchrony - Demo")
{
    window.setFramerateLimit(60);
}

void Game::run()
{
    //Bucle del juego principal
    while (window.isOpen()) {
        //inputs
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            scene_ptr->handle_event(event, window);
        }

        //Calcular
        scene_ptr->calculate(window);

        //Renderizar
        scene_ptr->render(window);
    }
}

void Game::set_scene(Scene& scene)
{
    scene_ptr = std::make_shared<Scene>(scene);
}