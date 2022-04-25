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

   // sf::RenderWindow window(sf::VideoMode(760, 840), "Pac-Man");

   // sf::Texture pacman_texture;
   // if (!pacman_texture.loadFromFile("C:\\Users\\Admin\\Pictures\\pacman.png")) {
   //     return 0;
   // }
   // sf::Sprite pacman_sprite;
   // pacman_sprite.setTexture(pacman_texture);
   // pacman_sprite.setOrigin(20, 20);
   // pacman_sprite.setPosition(20, 20);

   // GameWorld gameWorld = GameWorld();

   // while (window.isOpen())
   // {
   //     
   //     sf::Event event;
   //     while (window.pollEvent(event))
   //     {
   //         if (event.type == sf::Event::Closed)
   //             window.close();
   //         auto currentRotation = pacman_sprite.getRotation();
   //         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
   //             std::cout << ":-)"<<std::endl;
   //             pacman_sprite.rotate(0-currentRotation);
   //             pacman_sprite.move(40, 0);
   //         }
   //         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
   //             std::cout << ":-(" << std::endl;
   //             pacman_sprite.rotate(180-currentRotation);
   //             pacman_sprite.move(-40, 0);
   //         }
   //         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
   //             std::cout << ":->" << std::endl;
   //             pacman_sprite.rotate(270- currentRotation);
   //             pacman_sprite.move(0, -40);
   //         }
   //         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
   //             std::cout << ":-<" << std::endl;
   //             pacman_sprite.rotate(90-currentRotation);
   //             pacman_sprite.move(0, 40);
   //         }

   //     }

   //     window.clear();

   //     for (int i = 0; i < 21; i++) {
   //         for (int j = 0; j < 19; j++) {
   //             window.draw(gameWorld.tiles[i][j]->tile_sprite);
   //         }
   //     }

   //     window.draw(pacman_sprite);
   //     window.display();
   // }

    return 0;
}