#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#ifndef GHOST_H
#define GHOST_H

class Ghost {
public:

	Ghost(int posX, int posY);
	~Ghost() {};
	//?virtual bool setUpSprite(std::string);
	std::vector<sf::Vector2f> moveVector;
	sf::Vector2f position;
	sf::Sprite ghost_sprite;
	sf::RectangleShape ghostCollision;
	sf::Texture ghost_texture;

	void moveGhost(std::vector<sf::Vector2f>& moveVector);
	void updateGhost();
	virtual void loadTexture() = 0;
	void render(sf::RenderTarget* target);
	virtual void setUpMoveVector() = 0;

	/*void moveHorizontally(int offset);
	void moveVertically(int offset);*/
};

#endif