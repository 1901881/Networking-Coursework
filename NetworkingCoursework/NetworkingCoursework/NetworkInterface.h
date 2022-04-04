#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "ObjectInterface.h"


class NetworkInterface
{
public:
	//virtual void ////function name////////// = 0;

	virtual void runNetwork(unsigned short port) = 0;

	virtual void receivePacket() = 0; 
	//virtual void receivePlayerPacket(sf::Packet packet) = 0;
	//virtual void receiveBoxPacket(sf::Packet packet) = 0; 
	//virtual void receiveScorePacket(sf::Packet packet) = 0;

	virtual void sendMessage(ObjectInterface* object) = 0;
};

/*
Notes for tommorow:

take create and send messages away from server
take receive messages away from client

socket couldnt be transferred from classes write this down

add new receive and send functions to client and player
overide network interface functions


instead of ifs in game cpp update

on server or client creation 

pointer to interface then runNetwork

create point of player server or client

NetworkInterface = new ServerPlayer;

or

NetworkInterface = new ClientPlayer;
*/