#include "OrangeGhost.h"

OrangeGhost::OrangeGhost() : Ghost(420, 380)
{
	this->loadTexture();

	this->ghost_sprite.setTexture(this->ghost_texture);
	this->moveVector.push_back(sf::Vector2f(-40, 0));
	this->moveVector.push_back(sf::Vector2f(0, -80));
	this->setUpMoveVector();
}

void OrangeGhost::loadTexture() {
	this->ghost_texture.loadFromFile("C:\\Users\\Admin\\Documents\\GitHub\\a87312ac-gr41-repo\\Projekt\\pacman\\images\\orangeghost.png");
}

void OrangeGhost::setUpMoveVector()
{
	this->moveVector.push_back(sf::Vector2f(-120, 0));//1
	this->moveVector.push_back(sf::Vector2f(0, 80));//2
	this->moveVector.push_back(sf::Vector2f(-80, 0));//3
	this->moveVector.push_back(sf::Vector2f(0, 160));//4
	this->moveVector.push_back(sf::Vector2f(-120, 0));//5
	this->moveVector.push_back(sf::Vector2f(0, 80));//6
	this->moveVector.push_back(sf::Vector2f(40, 0));//7
	this->moveVector.push_back(sf::Vector2f(0, 80));//8
	this->moveVector.push_back(sf::Vector2f(-40, 0));//9
	this->moveVector.push_back(sf::Vector2f(0, 80));//10
	this->moveVector.push_back(sf::Vector2f(280, 0));//11
	this->moveVector.push_back(sf::Vector2f(0, -80));//12
	this->moveVector.push_back(sf::Vector2f(-80, 0));//13
	this->moveVector.push_back(sf::Vector2f(0, -80));//14
	this->moveVector.push_back(sf::Vector2f(80, 0));//15
	this->moveVector.push_back(sf::Vector2f(0, -80));//16
	this->moveVector.push_back(sf::Vector2f(-80, 0));//17
	this->moveVector.push_back(sf::Vector2f(0, -240));//18
	this->moveVector.push_back(sf::Vector2f(120, 0));//19
}
