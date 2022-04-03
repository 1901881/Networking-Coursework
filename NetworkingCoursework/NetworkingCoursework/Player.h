#pragma once
#include<SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "ObjectInterface.h"

using namespace std;

class Player : public ObjectInterface
{
public:
	Player(sf::RenderWindow* window, sf::Vector2f position, string textureName);
	~Player();


	//Interface Implementation//
	void Update(float dt) override;
	void Render() override;
	void Move(sf::Vector2f velocity) override { playerSprite.move(velocity); }

	///Sending Messages//
	sf::Packet createPacket();
	ObjectType getType() { return ObjectType::Player; }

	int getID() { return ID; }
	void setID(int ID) { this->ID = ID; }

	float getTimeSent() { return timeSent; }
	void setTimeSent(float timeSent) { this->timeSent = timeSent; }


	void HandleInput(float dt);
	void CheckCollision(float dt);
	void UpdateCollision(sf::FloatRect playerBounds, sf::FloatRect boxBounds);
	void PlayerRotate(int angle) { playerSprite.setRotation(angle); }


	int getAngle() { return angle; }
	sf::Vector2f getVelocity() { return velocity; };
	void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }
	sf::Sprite getSprite() { return playerSprite; };
	sf::Vector2f getPosition() { return playerSprite.getPosition();};
	void setPosition(sf::Vector2f position) { playerSprite.setPosition(position); }
	sf::Vector2f getNewBoxPositionAddOn() { return newBoxPositionAddOn; };
	void setNewBoxPositionAddOn(sf::Vector2f newBoxPositionAddOn) { this->newBoxPositionAddOn = newBoxPositionAddOn; }
	

private:

	sf::RenderWindow* window;

	sf::Sprite playerSprite;
	sf::Texture playerTexture;

	sf::Vector2f velocity;
	sf::Vector2f newBoxPositionAddOn = sf::Vector2f(0.0f, 0.0f);
	float boxSpeed = 1.0f;

	sf::FloatRect playerBounds;
	sf::FloatRect boxBounds;
	sf::FloatRect nextPos;

	float movementSpeed = 300.0f;

	int angle = 0;

	int ID;

	float timeSent;
};


