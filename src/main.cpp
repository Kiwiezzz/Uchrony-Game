#include "Core/Game.hpp"

int main()
{
    Game game;
    game.changeState(new MainMenu());
    game.run();
    return 0;
}
