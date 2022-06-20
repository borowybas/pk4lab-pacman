#pragma once
#include <SFML/Graphics.hpp>

#include "gameTile.h"
#include "Pacman.h"
#include "RedGhost.h"
#include "BlueGhost.h"
#include "OrangeGhost.h"
#include "PinkGhost.h"
#include "Point.h"

#include <vector>
#include <atomic>
#include <filesystem>

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld {
	//main game objects
	Pacman pacman;
	std::vector<Ghost*> ghostVec;
	std::vector < std::vector<GameTile*>> tiles; //map elements

	//objects for collision
	std::vector<sf::RectangleShape> mapCollisionElements;
	std::vector<sf::RectangleShape> colElements1;
	std::vector<sf::RectangleShape> colElements2;
	std::vector<sf::RectangleShape> foodRectangles;
	//other
	sf::VideoMode videomode;
	sf::RenderWindow* window;
	sf::Event myEvent;
	sf::Font font;
	sf::Text text;//score
	std::atomic<int> score = 0;
	sf::Text endText;
	std::filesystem::path path;
public:
	GameWorld();
	~GameWorld();

	void initWindow();
	void setUpTiles();
	void drawTiles();

	void setMapColPos();
	void setMapColPos2();
	void setUpCollisionVector();

	void pollEvents();//check if window is closed
	void render();
	void update();
	void updatePlayers();
	void updateCollision(const sf::RectangleShape& rectA, const sf::RectangleShape& rectB);
	void updateEating(const sf::RectangleShape& rectA);
	void updateDisplayScore();
	void updatePacGhostCollision(const sf::RectangleShape& tempPacShape, const sf::RectangleShape& tempGhostShape);
	
	void displayEndState(bool pacState);
	const bool runing() const { return this->window->isOpen(); };
};

#endif