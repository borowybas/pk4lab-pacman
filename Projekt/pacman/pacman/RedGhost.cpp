#include "RedGhost.h"

RedGhost::RedGhost(): Ghost(340, 380)
{
	this->loadTexture();
	
	this->ghost_sprite.setTexture(this->ghost_texture);
	this->setUpMoveVector();
}

void RedGhost::loadTexture() {
	this->ghost_texture.loadFromFile("C:\\Users\\Admin\\Documents\\GitHub\\a87312ac-gr41-repo\\Projekt\\pacman\\images\\redghost.png");
}

void RedGhost::setUpMoveVector()
{
	this->moveVector.push_back(sf::Vector2f(40, 0));
	this->moveVector.push_back(sf::Vector2f(0, 40));
	//this->moveVector.push_back(sf::Vector2f(0, -120));
	//this->moveVector.push_back(sf::Vector2f(0, 120));
}
