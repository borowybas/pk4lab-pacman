#pragma once
#include <SFML/Graphics.hpp>

#include "gameTile.h"
#include "Pacman.h"
//#include "Ghost.h"
#include "RedGhost.h"
#include "BlueGhost.h"
#include "OrangeGhost.h"
#include "PinkGhost.h"
#include <vector>
#include "Point.h"
#include <atomic>
#include <filesystem>
#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld {
	sf::Vector2i pacmanPos;
	void setUpInitialState();
	void setUpTiles();
	void drawTiles();

	//Pacman pacman;
	//bool isRunning;
	sf::VideoMode videomode;
	sf::RenderWindow* window;
	sf::Event myEvent;
	bool endGame;
	void initVariables();
	void initWindow();
public:
	std::vector < std::vector<GameTile*>> tiles; //map elements
	GameWorld();
	~GameWorld();
	void pollEvents();//check if window is closed
	sf::RectangleShape mapColEl1;
	std::vector<sf::RectangleShape> mapCollisionElements;
	std::vector<sf::RectangleShape> colElements1;
	std::vector<sf::RectangleShape> colElements2;
	void setMapColPos();
	void setMapColPos2();
	void setUpCollisionVector();
	Pacman pacman;
	//RedGhost redGhost;
	std::vector<Ghost*> ghostVec;
	void updateCollision(const sf::RectangleShape& rectA, const sf::RectangleShape& rectB);
	std::vector<sf::RectangleShape> foodRectangles;
	std::atomic<int> score = 0;
	void updateEating(const sf::RectangleShape& rectA);
	void update();
	void updatePlayer();
	void render();
	const bool runing() const { return this->window->isOpen(); };
	sf::Font font;
	sf::Text text;//score
	sf::Text endText;
	std::filesystem::path path;
	void updateDisplayScore();
	void updatePacGhostCollision(const sf::RectangleShape& tempPacShape, const sf::RectangleShape& tempGhostShape);
	void displayEndState(bool pacState);
};

#endif