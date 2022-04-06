#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

//Contains the message struct used for the networking

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
	int timeSent;//Time of the message sent, used for working out prediction
};

struct PlayerMessage : public BaseMessage
{
	int id; //Object number of the player within the game world
	float velocityX, velocityY; //Position of the player within the game world
	int angle;
	int timeSent;

	sf::Vector2f position;
	sf::Vector2f newBoxPositionAddOn;//Used for the box movement
	sf::FloatRect clientPlayerBounds;
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

	//Message type has to be encoded into an int for it to be sent across the network, 
	//this function is used when receiving the message to check the type of the message
	//so that the correct message receive function can be called
	MessageType decodeMessageType(int encodedMessageType) { return static_cast<MessageType>(encodedMessageType); }
	
	//Message setter and getters//
	//setters are used to update the object message with the new information after receiving a packet
	//getters are used to retrive the new information and set it within the empty game objects
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