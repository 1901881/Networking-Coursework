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

	sf::Vector2f getServerPlayerVelocity() { return serverPlayerVelocity; }

private:

	sf::IpAddress server;

	// Create a socket for communicating with the server
	sf::TcpSocket socket;

	Vector2f serverPlayerVelocity;
};

