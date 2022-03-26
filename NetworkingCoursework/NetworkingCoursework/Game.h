#pragma once
#include <SFML/Graphics.hpp>

#include "ServerPlayer.h"
#include "BoxManager.h"

#include <iostream>
#include <string>
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
	BoxManager* boxTest;

	sf::Font font;
	sf::Text titleText;
	sf::Text scoreTextLeft;
	sf::Text scoreTextRight;

	int scoreLeft = 0;
	int scoreRight = 0;
	

	// Draw functions
	void beginDraw();
	void endDraw();

};

