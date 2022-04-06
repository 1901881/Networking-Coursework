#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "NetworkMessages.h"
#include "NetworkInterface.h"
#include <iostream>
#include <vector>

using namespace sf;
//Inherits virtual class
class ServerPlayer : public NetworkInterface
{
public:
	ServerPlayer(unsigned short port);
	~ServerPlayer();

	void runNetwork(unsigned short port) override;
	void receivePacket() override;
	void sendMessage(ObjectInterface* object) override;

	//Receiving functions based from message type//
	void receivePlayerPacket(sf::Packet packet);

	//Prediction Functions//
	void addClientPlayerMessage(PlayerMessage& msg);//Updates the message vector with new message for prediction
	sf::Vector2f runPrediction(float dt) override; //return floats to update position


private:

	IpAddress ip = IpAddress::getLocalAddress();
	//server socket to accept new connections
	sf::TcpListener listener;

	sf::TcpSocket socket;

	std::vector<PlayerMessage> clientPlayerMessageVector;

	bool clientConnected = false;
};

