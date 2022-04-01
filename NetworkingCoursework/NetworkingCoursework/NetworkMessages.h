#pragma once

//Message struct for the use of updating the position and computing prediction
struct PlayerMessage
{
	int id; //Object number of the player within the game world
	float velocityX, velocityY; //Position of the player within the game world
	//float time; //Time of the message sent, used for working out prediction
	int angle;
	float timeSent;

	//id = 1 = Server
	//id = 2 = Client
};

struct BoxMessage
{
	int id; //Object number of the player within the game world
	float velocityX, velocityY; //Position of the player within the game world
};

struct ScoreMessage
{
	int scoreLeft;
	int scoreRight;
};