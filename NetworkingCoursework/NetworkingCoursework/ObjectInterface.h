#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>

enum class ObjectType
{
	Invalid = -1,
	Box,
	Player
};

class ObjectInterface
{

public:

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Move(sf::Vector2f velocity) = 0;
	
	virtual sf::Packet createPacket() = 0;
	virtual ObjectType getType() = 0;

	virtual int getID() = 0;
	virtual void setID(int ID) = 0;


};

