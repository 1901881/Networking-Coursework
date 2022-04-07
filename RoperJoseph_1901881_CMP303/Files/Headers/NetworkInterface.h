#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "ObjectInterface.h"


//This is a virtual class that will be inherited by the client and server classes
//All the functions will be changed by each network class to fit the use case
class NetworkInterface
{
public:

	virtual void runNetwork(unsigned short port) = 0;//Sets up the connection 

	virtual void receivePacket() = 0; //called when receiving messages

	virtual void sendMessage(ObjectInterface* object) = 0; //called when sending messages

	virtual sf::Vector2f runPrediction(float dt) = 0; //called when setting the players position after receiving data
};

