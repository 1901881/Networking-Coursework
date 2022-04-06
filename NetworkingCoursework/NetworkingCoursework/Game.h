#pragma once
#include <SFML/Graphics.hpp>

#include "ServerPlayer.h"
#include "ClientPlayer.h"
#include "Player.h"
#include "BoxManager.h"
#include "NetworkMessages.h"
#include "NetworkInterface.h"
#include "ScoreLine.h"

#include <iostream>
#include <string>
#include <chrono>

using namespace sf;

class Game
{
public:
	Game(sf::RenderWindow* hwnd);
	~Game();

	// Functions
	void update(float dt);
	void render(float dt);

	//Used to update the collision variables for the box and players
	void playerCollisionUpdate(Player* serverPlayer, Player* clientPlayer, BoxManager* box);
	void boxCollisionUpdate(Player* player, BoxManager* box);


private:
	// Background setup
	sf::RenderWindow* window;

	// Simulation elements
	NetworkInterface* networkObject;
	Player* serverPlayer;
	Player* clientPlayer;
	ScoreLine* scoreLine;
	BoxManager* boxTest;

	// Choose an arbitrary port for opening sockets
	const unsigned short port = 50001;

	//Used at the start of the program 
	//for the user to choose whether they want to be a client or server
	bool serverBool = false;
	bool clientBool = false;

	int latency;//used for limiting messages sent

	float gameTime = 0;//used to calculate prediction

	// Draw functions
	void beginDraw();
	void endDraw();

};

