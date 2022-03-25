#pragma once
#include <SFML/Graphics.hpp>

#include "ServerPlayer.h"
#include "BoxManager.h"

#include <iostream>
using namespace sf;

class Game
{
public:
	Game(sf::RenderWindow* hwnd);
	~Game();

	// Functions
	void update(float dt);
	void render(float dt);

private:
	int boxAmount = 5;

	// Background setup
	sf::RenderWindow* window;

	// Simulation elements
	ServerPlayer* serverPlayer;
	BoxManager* boxManager[5];

	sf::RectangleShape scoreLine;
	std::vector<BoxManager*> boxes;
	

	// Draw functions
	void beginDraw();
	void endDraw();

};

