#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

#include "NetworkMessages.h"

using namespace sf;

class ClientPlayer
{
public:
	ClientPlayer(unsigned short port);
	~ClientPlayer();
	void runTcpClient(unsigned short port);
	void receivePlayerMessage();
	void receiveBoxMessage();
	void receiveScoreMessage();

	void addServerPlayerMessage(PlayerMessage& msg);

	sf::Vector2f runPrediction(float dt);

	sf::Vector2f getServerPlayerVelocity() { return serverPlayerVelocity; }
	PlayerMessage getServerPlayerMessage() { return serverPlayerMessage; }
	BoxMessage getBoxMessage() { return boxMessage; }
	ScoreMessage getScoreMessage() { return scoreMessage; }
	

private:

	sf::IpAddress server;

	// Create a socket for communicating with the server
	sf::TcpSocket socket;


	std::vector<PlayerMessage> serverPlayerMessageVector;
	PlayerMessage serverPlayerMessage;
	BoxMessage boxMessage;
	ScoreMessage scoreMessage;

	Vector2f serverPlayerVelocity;
	float serverPlayerAngle;
};

