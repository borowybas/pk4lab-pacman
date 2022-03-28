#include <SFML/Graphics.hpp>
#include <iostream>

#include "gameWorld.h"
#include "gameTile.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "Pac-Man");
    //sf::CircleShape shape(10.f);
   // shape.setFillColor(sf::Color::Yellow);

    sf::Texture pacman_texture;
    if (!pacman_texture.loadFromFile("C:\\Users\\Admin\\Pictures\\pacman.png")) {
        return 0;
    }
    sf::Sprite spacman_sprite;
    spacman_sprite.setTexture(pacman_texture);

    GameWorld gameWorld = GameWorld();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                std::cout << ":-)"<<std::endl;
                spacman_sprite.move(40, 0);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                std::cout << ":-(" << std::endl;
                spacman_sprite.move(-40, 0);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                std::cout << ":->" << std::endl;
                spacman_sprite.move(0, -40);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                std::cout << ":-<" << std::endl;
                spacman_sprite.move(0, 40);
            }

        }

        window.clear();

        for (int i = 0; i < 21; i++) {
            for (int j = 0; j < 19; j++) {
                window.draw(gameWorld.tiles[i][j]->tile_sprite);
            }
        }

        window.draw(spacman_sprite);
        window.display();
    }

    return 0;
}