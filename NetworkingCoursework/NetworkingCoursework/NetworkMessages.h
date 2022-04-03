#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "ObjectInterface.h"
#include <iostream>

enum class MessageType : int
{
	Invalid = -1,
	Player,
	Box,
	Score
};

MessageType decodeMessageType(int encodedMessageType) { return static_cast<MessageType>(encodedMessageType); }

struct BaseMessage
{
	int encodedMessageType;
	int timeSent;
};

//Message struct for the use of updating the position and computing prediction
struct PlayerMessage : public BaseMessage
{
	int id; //Object number of the player within the game world
	float velocityX, velocityY; //Position of the player within the game world
	//float time; //Time of the message sent, used for working out prediction
	int angle;
	int timeSent;

	sf::Vector2f position;

	//id = 1 = Server
	//id = 2 = Client
};

struct BoxMessage : public BaseMessage
{
	int id; //Object number of the player within the game world
	float velocityX, velocityY; //Position of the player within the game world

	sf::Vector2f position;
};

struct ScoreMessage : public BaseMessage
{
	int scoreLeft;
	int scoreRight;
};


void receivePacket(sf::TcpSocket socket);
void receivePlayerPacket(sf::Packet packet);
void receiveBoxPacket(sf::Packet packet);
void receiveScorePacket(sf::Packet packet);

void sendMessage(sf::TcpSocket socket, sf::Packet packet);
void sendPlayerPacket(sf::TcpSocket socket, sf::Packet packet);
void sendBoxPacket(sf::TcpSocket socket, sf::Packet packet);
void sendScorePacket(sf::TcpSocket socket, sf::Packet packet);

namespace NetworkContainer
{
	PlayerMessage playerMessage;
	BoxMessage boxMessage;
	ScoreMessage scoreMessage;
}



