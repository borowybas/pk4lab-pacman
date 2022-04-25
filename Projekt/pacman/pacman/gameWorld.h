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

	Pacman pacman;
	//bool isRunning;

	sf::VideoMode videomode;
	sf::RenderWindow* window;
	sf::Event myEvent;
	bool endGame;
	void initVariables();
	void initWindow();
public:

	std::vector < std::vector<GameTile*>> tiles;
	int gridLength;
	int gridHeight;
	GameWorld();
	~GameWorld();
	void pollEvents();
	void handleEvents();
	void update();
	void updatePlayer();
	void render();
	void clean();
	const bool runing() const { return this->window->isOpen(); };
};

#endif