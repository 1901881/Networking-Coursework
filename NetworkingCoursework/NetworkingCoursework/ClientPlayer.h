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

	sf::Vector2f getServerPlayerVelocity() { return serverPlayerVelocity; }
	PlayerMessage getServerPlayerMessage() { return serverPlayerMessage; }
	BoxMessage getBoxMessage() { return boxMessage; }
	

private:

	sf::IpAddress server;

	// Create a socket for communicating with the server
	sf::TcpSocket socket;


	PlayerMessage serverPlayerMessage;
	BoxMessage boxMessage;

	Vector2f serverPlayerVelocity;
	float serverPlayerAngle;
};

