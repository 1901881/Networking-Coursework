#pragma once
#include<SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "ObjectInterface.h"

using namespace std;

class Player : public ObjectInterface
{
public:
	Player(sf::RenderWindow* window, sf::Vector2f position, string textureName, int ID);
	~Player();


	//Interface Implementation//
	void Update(float dt) override;
	void Render() override;
	void Move(sf::Vector2f velocity) override { playerSprite.move(velocity); }

	///Sending Messages//
	sf::Packet createPacket() override;
	ObjectType getObjectType() override { return ObjectType::Player; } 
	MessageType getMessageType() override { return MessageType::Player; } 

	int getID() override { return ID; }
	void setID(int ID) override { this->ID = ID; }

	void setTimeSent(float timeSent) { this->timeSent = timeSent; }

	sf::Vector2f getVelocity() override { return velocity; }
	sf::Vector2f getPosition() override { return playerSprite.getPosition(); }
	float getTimeSent() override { return timeSent; }
	int getAngle() override { return angle; }


	void HandleInput(float dt);
	void CheckCollision(float dt);
	void UpdateCollision(sf::FloatRect playerBounds, sf::FloatRect boxBounds);
	void PlayerRotate(int angle) { playerSprite.setRotation(angle); }



	void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }
	sf::Sprite getSprite() { return playerSprite; };
	void setPosition(sf::Vector2f position) { playerSprite.setPosition(position); }
	sf::Vector2f getNewBoxPositionAddOn() { return newBoxPositionAddOn; };
	void setNewBoxPositionAddOn(sf::Vector2f newBoxPositionAddOn) { this->newBoxPositionAddOn = newBoxPositionAddOn; }
	
	void setServerBool(bool serverBool) { this->serverBool = serverBool; }
	void setClientBool(bool clientBool) { this->clientBool = clientBool; }

private:

	sf::RenderWindow* window;

	sf::Sprite playerSprite;
	sf::Texture playerTexture;

	sf::Vector2f velocity;
	sf::Vector2f newBoxPositionAddOn = sf::Vector2f(0.0f, 0.0f);
	float boxSpeed = 1.0f;

	sf::FloatRect playerBounds;//might need to send these over to server.
	sf::FloatRect boxBounds;
	sf::FloatRect nextPos;

	float movementSpeed = 300.0f;

	int angle = 0;

	int ID = 0;

	float timeSent = 0;

	bool serverBool = false;
	bool clientBool = false;

};


