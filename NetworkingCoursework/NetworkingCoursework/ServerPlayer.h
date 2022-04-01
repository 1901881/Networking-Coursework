#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "NetworkMessages.h"
#include <iostream>

using namespace sf;

class ServerPlayer
{
public:
	ServerPlayer(unsigned short port);
	~ServerPlayer();

	void runTcpServer(unsigned short port);
	void createPlayerMessage(int id, sf::Vector2f velocity, float angle);
	void sendPlayerMessage(PlayerMessage serverPlayerMessage);

	void createBoxMessage(int id, sf::Vector2f velocity);
	void sendBoxMessage(BoxMessage boxMessage);

	void createScoreMessage(int scoreLeft, int scoreRight);
	void sendScoreMessage(ScoreMessage scoreMessage);
private:

	IpAddress ip = IpAddress::getLocalAddress();
	// Create a server socket to accept new connections
	sf::TcpListener listener;

	sf::TcpSocket socket;

	bool clientConnected = false;
};

