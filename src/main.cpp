#include "Core/Game.hpp"

int main()
{
    Game game;
    game.changeState(new Screen1());
    game.run();
    return 0;
}
