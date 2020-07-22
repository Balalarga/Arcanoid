#include <iostream>
#include "game.h"

using namespace std;

int main(int argc, char** argv)
{
    Game::initGame(1024, 720);
    Game::startGame();
    return 0;
}
