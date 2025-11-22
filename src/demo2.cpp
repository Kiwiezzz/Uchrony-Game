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
    Scene scene("assets/textures/suelo.png", "assets/textures/escenario_colision.png"); 
    
    SpriteInfo mesa("assets/textures/mesa.png");
    mesa.sprite.setPosition(397, 494);
    mesa.sprite.setOrigin(mesa.texture->getSize().x / 2.f, mesa.texture->getSize().y);
    mesa.sprite.setScale(1.0f, 1.0f);

    SpriteInfo mesa2("assets/textures/mesa_2.png");
    mesa2.sprite.setPosition(743, 354);
    mesa2.sprite.setOrigin(mesa.texture->getSize().x / 2.f, mesa.texture->getSize().y); //Esto debe estar en mesa si no se aloca
    mesa2.sprite.setScale(1.0f, 1.0f);

    SpriteInfo botella("assets/textures/botella.png");
    botella.sprite.setPosition(597, 185);

    scene.add_entity(mesa);
    scene.add_entity(mesa2);
    scene.add_entity(botella);

    Game game;
    game.set_scene(scene);
    game.run();

    return 0;
}/**/