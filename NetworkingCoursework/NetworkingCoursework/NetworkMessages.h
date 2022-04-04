#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

enum class MessageType : int
{
	Invalid = -1,
	Player = 0,
	Box,
	Score
};

struct BaseMessage
{
	int encodedMessageType;
	int timeSent;
};

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


class NetworkMessages
{
public:

	MessageType decodeMessageType(int encodedMessageType) { return static_cast<MessageType>(encodedMessageType); }
	
	void setPlayerMessage(PlayerMessage playerMessage) { 
		this->playerMessage = playerMessage; }
	PlayerMessage getPlayerMessage() { return playerMessage; }

	void setBoxMessage(BoxMessage boxMessage) { this->boxMessage = boxMessage; }
	BoxMessage getBoxMessage() { return boxMessage; }

	void setScoreMessage(ScoreMessage scoreMessage) { this->scoreMessage = scoreMessage; }
	ScoreMessage getScoreMessage() { return scoreMessage; }

private:

	PlayerMessage playerMessage;
	BoxMessage boxMessage;
	ScoreMessage scoreMessage;
};







/*
1
1
not
2
2
kermit
your mum
zara 
merry berry with a hat
your sister


*/