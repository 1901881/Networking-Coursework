#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

#include "NetworkMessages.h"
#include "NetworkInterface.h"

#include <vector>

using namespace sf;
//Inherits virtual class
class ClientPlayer : public NetworkInterface
{
public:
	ClientPlayer(unsigned short port);
	~ClientPlayer();

	void runNetwork(unsigned short port) override;
	void sendMessage(ObjectInterface* object) override;
	void receivePacket() override;

	//Receiving functions based from message type//
	void receivePlayerPacket(sf::Packet packet);
	void receiveBoxPacket(sf::Packet packet);
	void receiveScorePacket(sf::Packet packet);

	//Prediction Functions//
	void addServerPlayerMessage(PlayerMessage& msg);//Updates the message vector with new message for prediction
	sf::Vector2f runPrediction(float dt) override;//return floats to update position


	

private:

	sf::IpAddress server;

	//socket for communicating with the server
	sf::TcpSocket socket;

	std::vector<PlayerMessage> serverPlayerMessageVector;

	Vector2f serverPlayerVelocity;
	float serverPlayerAngle;

};

