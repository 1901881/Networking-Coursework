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

using std::chrono::duration_cast;
using std::chrono::seconds;
typedef std::chrono::steady_clock timingsClock;

using namespace sf;

class Game
{
public:
	Game(sf::RenderWindow* hwnd);
	~Game();

	// Functions
	void update(float dt);
	void render(float dt);
	void initScoreLine();
	void initText();
	void scoreLineUpdate();
	void setScoreLineText();
	void playerCollisionUpdate(Player* player, BoxManager* box);
	void boxCollisionUpdate(Player* player, BoxManager* box);


private:
	int boxAmount = 5;

	// Background setup
	sf::RenderWindow* window;

	// Simulation elements
	NetworkInterface* networkObject;
	//ServerPlayer* server;
	//ClientPlayer* client;
	Player* serverPlayer;
	Player* clientPlayer;
	ScoreLine* scoreLine;
	//BoxManager* boxManager[5];

	//sf::RectangleShape scoreLine;
	//std::vector<BoxManager*> boxes;


	BoxManager* boxTest;

	sf::Font font;
	sf::Text titleText;
	sf::Text scoreTextLeft;
	sf::Text scoreTextRight;

	int scoreLeft = 0;
	int scoreRight = 0;

	// Choose an arbitrary port for opening sockets
	const unsigned short port = 50001;
	bool serverBool = false;
	bool clientBool = false;

	int latency;

	float gameTime = 0;

	// Draw functions
	void beginDraw();
	void endDraw();

};

