#include "Game.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "Uchrony - Demo")
{
    window.setFramerateLimit(60);
}

void Game::run()
{
    //Bucle del juego principal
    while (window.isOpen()) {
        current_scene->dt = clock.restart();
        
        //inputs
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
        
            current_scene->handle_event(event, window);
        }

        current_scene->calculate(window);
        current_scene->render(window);

        window.display();
    }
}

void Game::set_scene(Scene& scene)
{
    current_scene = std::make_shared<Scene>(scene);
}