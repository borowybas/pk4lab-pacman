#pragma once
#include <SFML/Graphics.hpp>

#include "gameTile.h"
#include "Pacman.h"
#include <vector>

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
	//int gridLength;
	//int gridHeight;
	GameWorld();
	~GameWorld();
	void pollEvents();//check if window is closed
	//void handleEvents();
	sf::RectangleShape mapColEl1;
	void setMapColPos();
	Pacman pacman;
	void updateCollision(const sf::RectangleShape& rectA, const sf::RectangleShape& rectB);

	void update();
	void updatePlayer();
	void render();
	const bool runing() const { return this->window->isOpen(); };
};

#endif