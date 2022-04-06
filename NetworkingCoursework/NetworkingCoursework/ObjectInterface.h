#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>

#include "NetworkMessages.h"

//Used when defining which object message to send
enum class ObjectType
{
	Invalid = -1,
	Box,
	Player,
	Score
};

//This is a virtual class that will be inherited by the game object classes; player, box, scoreline
//All the functions will be changed by each object class to fit the use case
class ObjectInterface
{

public:

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Move(sf::Vector2f velocity) = 0;
	
	virtual sf::Packet createPacket() = 0;
	virtual ObjectType getObjectType() = 0;
	virtual MessageType getMessageType() = 0;

	virtual int getID() = 0;
	virtual void setID(int ID) = 0;

	virtual sf::Vector2f getVelocity() = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual float getTimeSent() = 0;
	virtual int getAngle() = 0;


};

