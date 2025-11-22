#ifndef SCENE_HPP
#define SCENE_HPP

#include "SpriteInfo.hpp"
#include "Entities/Player.hpp"
#include "Utils/GameUtilities.hpp"

#include <unordered_map>


class Scene {
public:
    Scene(std::string background_path, std::string collision_image_path);
 
    ~Scene();

    void add_entity(const SpriteInfo& entity);

    void handle_event(sf::Event event, sf::RenderWindow& window);

    void calculate(sf::RenderWindow& window);

    void render(sf::RenderWindow& window);

private:
    sf::Time dt;
    sf::Clock clock;

    SpriteInfo background;
    sf::Image collision_image;
    
    Player player; //Esta es una clase de isaac
    std::vector<SpriteInfo> entities;
    
    bool isDebugPlacing;

    
};

#endif /* SCENE_HPP */