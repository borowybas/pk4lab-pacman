#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#ifndef GHOST_H
#define GHOST_H

class Ghost {
public:
	std::vector<sf::Vector2f> moveVector;
	sf::Vector2f position;
	sf::RectangleShape ghostCollision;
	sf::Sprite ghost_sprite;
	sf::Texture ghost_texture;

	Ghost(int posX, int posY);
	~Ghost() {};

	void moveGhost(std::vector<sf::Vector2f>& moveVector);
	void updateGhost();
	void render(sf::RenderTarget* target);

	virtual void loadTexture() = 0;
	virtual void setUpMoveVector() = 0;
};

#endif