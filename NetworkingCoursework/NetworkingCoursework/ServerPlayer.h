#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "NetworkMessages.h"
#include "NetworkInterface.h"
#include <iostream>
#include <vector>

using namespace sf;

class ServerPlayer : public NetworkInterface
{
public:
	ServerPlayer(unsigned short port);
	~ServerPlayer();

	void runNetwork(unsigned short port) override;
	void receivePacket() override;
	void sendMessage(ObjectInterface* object) override;


	void receivePlayerPacket(sf::Packet packet);
	void receiveBoxPacket(sf::Packet packet);
	void receiveScorePacket(sf::Packet packet);

	void addClientPlayerMessage(PlayerMessage& msg);
	sf::Vector2f runPrediction(float dt) override;


private:

	IpAddress ip = IpAddress::getLocalAddress();
	// Create a server socket to accept new connections
	sf::TcpListener listener;

	sf::TcpSocket socket;

	std::vector<PlayerMessage> clientPlayerMessageVector;

	bool clientConnected = false;
};

