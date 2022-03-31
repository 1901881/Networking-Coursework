#pragma once

//Message struct for the use of updating the position and computing prediction
struct PlayerMessage
{
	int id; //Object number of the player within the game world
	float velocityX, velocityY; //Position of the player within the game world
	//float time; //Time of the message sent, used for working out prediction
	int angle;


	//id = 1 = Server
	//id = 2 = Client
};

struct BoxMessage
{

};

struct ScoreMessage
{

};