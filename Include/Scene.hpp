#ifndef SCENE_HPP
#define SCENE_HPP

#include "SpriteInfo.hpp"
#include "Entities/Player.hpp"
#include "Utils/GameUtilities.hpp"

class Scene {
public:
    Scene();
 
    ~Scene();

    void handle_event(sf::Event event, sf::RenderWindow& window);

    void calculate(sf::RenderWindow& window);

    void render(sf::RenderWindow& window);

    sf::Time dt;

private:
    SpriteInfo background;
    
    Player player; //Esta es una clase de isaac
    
    sf::Image collision_image;

    //std::map entities;

    std::vector<sf::Sprite*> renderList;

    std::vector<SpriteInfo> list;

    bool isDebugPlacing;

    
};

#endif /* SCENE_HPP */