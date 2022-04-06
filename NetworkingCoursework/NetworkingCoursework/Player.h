#pragma once
#include<SFML/Graphics.hpp>
#include <vector>
#include <iostream> //used for debug messages
#include "ObjectInterface.h"

using namespace std;

//Inherits virtual class
class Player : public ObjectInterface
{
public:
	Player(sf::RenderWindow* window, sf::Vector2f position, string textureName, int ID); //Sets the player
	~Player();

	//Interface Implementation//
	void Update(float dt) override;
	void Render() override;
	void Move(sf::Vector2f velocity) override { playerSprite.move(velocity); }

	//Networking functions//
	sf::Packet createPacket() override;
	ObjectType getObjectType() override { return ObjectType::Player; } 
	MessageType getMessageType() override { return MessageType::Player; } 
	int getID() override { return ID; }
	void setID(int ID) override { this->ID = ID; }
	sf::Vector2f getVelocity() override { return velocity; }
	sf::Vector2f getPosition() override { return playerSprite.getPosition(); }
	float getTimeSent() override { return timeSent; }
	int getAngle() override { return angle; }


	//Players own functions//
	void HandleInput(float dt);//Receives keyboard input and moves player
	void CheckCollision(float dt);//Checks whether player is with game bounds
	void UpdateCollision(sf::FloatRect servePlayerBounds, sf::FloatRect clientPlayerBounds, sf::FloatRect boxBounds);//Gets players next position for collision with box and level border
	void PlayerRotate(int angle) { playerSprite.setRotation(angle); }//Used to rotate the player so that it matches the movement


	void setTimeSent(float timeSent) { this->timeSent = timeSent; }
	void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }
	sf::Sprite getSprite() { return playerSprite; };
	void setPosition(sf::Vector2f position) { playerSprite.setPosition(position); }
	sf::Vector2f getNewBoxPositionAddOn() { return newBoxPositionAddOn; };
	void setNewBoxPositionAddOn(sf::Vector2f newBoxPositionAddOn) { this->newBoxPositionAddOn = newBoxPositionAddOn; }
	void setClientPlayerBounds(sf::FloatRect clientPlayerBounds) { this->externalPlayerBounds = clientPlayerBounds; }
	sf::FloatRect getClientPlayerBounds() { return externalPlayerBounds; }

	//Used for changing player controls between applications
	void setServerBool(bool serverBool) { this->serverBool = serverBool; }
	void setClientBool(bool clientBool) { this->clientBool = clientBool; }

private:

	sf::RenderWindow* window;

	//Player Variables//
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	sf::Vector2f velocity;
	float movementSpeed = 300.0f;
	int angle = 0;
	bool serverBool = false;
	bool clientBool = false;

	//Box Movement//
	sf::Vector2f newBoxPositionAddOn = sf::Vector2f(0.0f, 0.0f);
	float boxSpeed = 1.0f;
	sf::FloatRect currentPlayerBounds;
	sf::FloatRect externalPlayerBounds;
	sf::FloatRect boxBounds;
	sf::FloatRect nextPos;

	//Networking variables//
	int ID = 0;
	float timeSent = 0;



};


