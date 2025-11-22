#ifndef SCENE_HPP
#define SCENE_HPP

#include "Entities/Player.hpp"
#include "Utils/GameUtilities.hpp"

#include <unordered_map>


class Scene {
public:
    Scene(std::string background_path, std::string collision_image_path);
 
    ~Scene();

    void add_entity();

    void handle_event();

    void calculate();

    void render();

private:

    // background;
    sf::Image collision_image;
    
    Player player; //Esta es una clase de isaac
    //std::vector<SpriteInfo> entities;
    
    bool isDebugPlacing;

    
};

#endif /* SCENE_HPP */