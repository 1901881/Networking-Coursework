#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

#include "NetworkMessages.h"
#include "NetworkInterface.h"

using namespace sf;

class ClientPlayer : public NetworkInterface
{
public:
	ClientPlayer(unsigned short port);
	~ClientPlayer();
	void runNetwork(unsigned short port) override;

	void sendMessage(ObjectInterface* object) override;
	void receivePacket() override;


	void receivePlayerPacket(sf::Packet packet);
	void receiveBoxPacket(sf::Packet packet);
	void receiveScorePacket(sf::Packet packet);


	void addServerPlayerMessage(PlayerMessage& msg);
	sf::Vector2f runPrediction(float dt);


	

private:

	sf::IpAddress server;

	// Create a socket for communicating with the server
	sf::TcpSocket socket;


	//std::vector<PlayerMessage> serverPlayerMessageVector;
	//PlayerMessage serverPlayerMessage;
	//BoxMessage boxMessage;
	//ScoreMessage scoreMessage;

	Vector2f serverPlayerVelocity;
	float serverPlayerAngle;

};

