#include "BlueGhost.h"

BlueGhost::BlueGhost(): Ghost(380, 380)
{
	this->loadTexture();
	
	this->ghost_sprite.setTexture(this->ghost_texture);
	this->moveVector.push_back(sf::Vector2f(0, -80));
	this->setUpMoveVector();
}

void BlueGhost::loadTexture() {
	this->ghost_texture.loadFromFile("C:\\Users\\Admin\\Documents\\GitHub\\a87312ac-gr41-repo\\Projekt\\pacman\\images\\blueghost.png");
}

void BlueGhost::setUpMoveVector()
{
	this->moveVector.push_back(sf::Vector2f(40, 0));//1
	this->moveVector.push_back(sf::Vector2f(0, -80));//2
	this->moveVector.push_back(sf::Vector2f(80, 0));//3
	this->moveVector.push_back(sf::Vector2f(0, -80));//4
	this->moveVector.push_back(sf::Vector2f(-80, 0));//5
	this->moveVector.push_back(sf::Vector2f(0, -80));//6
	this->moveVector.push_back(sf::Vector2f(280, 0));//7
	this->moveVector.push_back(sf::Vector2f(0, 160));//8
	this->moveVector.push_back(sf::Vector2f(-120, 0));//9
	this->moveVector.push_back(sf::Vector2f(0, 160));//10
	this->moveVector.push_back(sf::Vector2f(-80, 0));//11
	this->moveVector.push_back(sf::Vector2f(0, -80));//12
	this->moveVector.push_back(sf::Vector2f(-120, 0));//13
}
