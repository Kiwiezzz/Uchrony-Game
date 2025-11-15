#ifndef GAME_CPP
#define GAME_CPP

#include <memory>

#include "Scene.hpp"

class Game
{
    sf::RenderWindow window;
    
    sf::Clock clock;

    std::shared_ptr<Scene> current_scene;
    
public: 

    Game();

    void run();

    void set_scene(Scene& scene);

};

#endif