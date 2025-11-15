#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#include "Utils/GameUtilities.hpp" 
#include "Entities/Player.hpp"

#include "SpriteInfo.hpp"
#include "Scene.hpp"
#include "Game.hpp"

int main() {
    Scene scene; 
    
    Game game;
    
    
    game.set_scene(scene);

    game.run();

    return 0;
}/**/