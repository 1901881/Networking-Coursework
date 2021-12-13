#pragma once
#include "Server.h"
#include "Client.h"
#include "Player.h"

#include <SFML/Network.hpp>
#include<SFML/Graphics.hpp>

class Game
{
public:
	void setupTCPServer();
	void setupTCPClient();
	void runGame(); //creates the window for gameplay 

	void HandleInput();
	void update(); //used to update the game and player position
	void render(); //used to render the objects and players


private:
	Server serverObj;
	Client clientObj;
	Player playerObj;

	int serverPlayerID;
	int clientPlayerID;

	sf::RenderWindow serverWindow;
	sf::RenderWindow clientWindow;

	bool updateWindow = false;
};

