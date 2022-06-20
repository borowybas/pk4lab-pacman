#include <SFML/Graphics.hpp>

#include <iostream>

#include "gameWorld.h"
#include "gameTile.h"
#include "Pacman.h"

int main()
{
    GameWorld Game;

    while (Game.runing()) {
        Game.update();
        Game.render();
    }

    return 0;
}